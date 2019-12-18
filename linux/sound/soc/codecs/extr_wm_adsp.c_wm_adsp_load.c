#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wmfw_region {int /*<<< orphan*/  len; int /*<<< orphan*/  data; int /*<<< orphan*/  type; int /*<<< orphan*/  offset; } ;
struct wmfw_header {int /*<<< orphan*/  len; int /*<<< orphan*/  core; int /*<<< orphan*/  ver; int /*<<< orphan*/ * magic; } ;
struct wmfw_footer {int /*<<< orphan*/  timestamp; } ;
struct wmfw_adsp1_sizes {int dummy; } ;
struct wm_adsp_region {int dummy; } ;
struct wm_adsp_buf {int /*<<< orphan*/  buf; } ;
struct wm_adsp {char* part; char* fwf_name; size_t fw; TYPE_1__* ops; int /*<<< orphan*/  type; int /*<<< orphan*/  fw_ver; int /*<<< orphan*/  dev; struct regmap* regmap; } ;
struct regmap {int dummy; } ;
struct firmware {unsigned int size; int /*<<< orphan*/ * data; } ;
struct TYPE_4__ {char* file; } ;
struct TYPE_3__ {unsigned int (* parse_sizes ) (struct wm_adsp*,char*,unsigned int,struct firmware const*) ;unsigned int (* region_to_reg ) (struct wm_adsp_region const*,int) ;int /*<<< orphan*/  (* validate_version ) (struct wm_adsp*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int PAGE_SIZE ; 
#define  WMFW_ABSOLUTE 139 
#define  WMFW_ADSP1_DM 138 
#define  WMFW_ADSP1_PM 137 
#define  WMFW_ADSP1_ZM 136 
#define  WMFW_ADSP2_XM 135 
#define  WMFW_ADSP2_YM 134 
#define  WMFW_ALGORITHM_DATA 133 
#define  WMFW_HALO_PM_PACKED 132 
#define  WMFW_HALO_XM_PACKED 131 
#define  WMFW_HALO_YM_PACKED 130 
#define  WMFW_INFO_TEXT 129 
#define  WMFW_NAME_TEXT 128 
 int /*<<< orphan*/  adsp_dbg (struct wm_adsp*,char*,char*,int,...) ; 
 int /*<<< orphan*/  adsp_err (struct wm_adsp*,char*,...) ; 
 int /*<<< orphan*/  adsp_info (struct wm_adsp*,char*,char*,...) ; 
 int /*<<< orphan*/  adsp_warn (struct wm_adsp*,char*,char*,int,unsigned int,...) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_list ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int regmap_async_complete (struct regmap*) ; 
 int regmap_raw_write_async (struct regmap*,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  stub1 (struct wm_adsp*,int /*<<< orphan*/ ) ; 
 unsigned int stub2 (struct wm_adsp*,char*,unsigned int,struct firmware const*) ; 
 unsigned int stub3 (struct wm_adsp_region const*,int) ; 
 struct wm_adsp_buf* wm_adsp_buf_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wm_adsp_buf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wm_adsp_debugfs_save_wmfwname (struct wm_adsp*,char*) ; 
 struct wm_adsp_region* wm_adsp_find_region (struct wm_adsp*,int) ; 
 TYPE_2__* wm_adsp_fw ; 
 char* wm_adsp_mem_region_name (int) ; 
 int wm_adsp_parse_coeff (struct wm_adsp*,struct wmfw_region const*) ; 

__attribute__((used)) static int wm_adsp_load(struct wm_adsp *dsp)
{
	LIST_HEAD(buf_list);
	const struct firmware *firmware;
	struct regmap *regmap = dsp->regmap;
	unsigned int pos = 0;
	const struct wmfw_header *header;
	const struct wmfw_adsp1_sizes *adsp1_sizes;
	const struct wmfw_footer *footer;
	const struct wmfw_region *region;
	const struct wm_adsp_region *mem;
	const char *region_name;
	char *file, *text = NULL;
	struct wm_adsp_buf *buf;
	unsigned int reg;
	int regions = 0;
	int ret, offset, type;

	file = kzalloc(PAGE_SIZE, GFP_KERNEL);
	if (file == NULL)
		return -ENOMEM;

	snprintf(file, PAGE_SIZE, "%s-%s-%s.wmfw", dsp->part, dsp->fwf_name,
		 wm_adsp_fw[dsp->fw].file);
	file[PAGE_SIZE - 1] = '\0';

	ret = request_firmware(&firmware, file, dsp->dev);
	if (ret != 0) {
		adsp_err(dsp, "Failed to request '%s'\n", file);
		goto out;
	}
	ret = -EINVAL;

	pos = sizeof(*header) + sizeof(*adsp1_sizes) + sizeof(*footer);
	if (pos >= firmware->size) {
		adsp_err(dsp, "%s: file too short, %zu bytes\n",
			 file, firmware->size);
		goto out_fw;
	}

	header = (void *)&firmware->data[0];

	if (memcmp(&header->magic[0], "WMFW", 4) != 0) {
		adsp_err(dsp, "%s: invalid magic\n", file);
		goto out_fw;
	}

	if (!dsp->ops->validate_version(dsp, header->ver)) {
		adsp_err(dsp, "%s: unknown file format %d\n",
			 file, header->ver);
		goto out_fw;
	}

	adsp_info(dsp, "Firmware version: %d\n", header->ver);
	dsp->fw_ver = header->ver;

	if (header->core != dsp->type) {
		adsp_err(dsp, "%s: invalid core %d != %d\n",
			 file, header->core, dsp->type);
		goto out_fw;
	}

	pos = sizeof(*header);
	pos = dsp->ops->parse_sizes(dsp, file, pos, firmware);

	footer = (void *)&firmware->data[pos];
	pos += sizeof(*footer);

	if (le32_to_cpu(header->len) != pos) {
		adsp_err(dsp, "%s: unexpected header length %d\n",
			 file, le32_to_cpu(header->len));
		goto out_fw;
	}

	adsp_dbg(dsp, "%s: timestamp %llu\n", file,
		 le64_to_cpu(footer->timestamp));

	while (pos < firmware->size &&
	       sizeof(*region) < firmware->size - pos) {
		region = (void *)&(firmware->data[pos]);
		region_name = "Unknown";
		reg = 0;
		text = NULL;
		offset = le32_to_cpu(region->offset) & 0xffffff;
		type = be32_to_cpu(region->type) & 0xff;

		switch (type) {
		case WMFW_NAME_TEXT:
			region_name = "Firmware name";
			text = kzalloc(le32_to_cpu(region->len) + 1,
				       GFP_KERNEL);
			break;
		case WMFW_ALGORITHM_DATA:
			region_name = "Algorithm";
			ret = wm_adsp_parse_coeff(dsp, region);
			if (ret != 0)
				goto out_fw;
			break;
		case WMFW_INFO_TEXT:
			region_name = "Information";
			text = kzalloc(le32_to_cpu(region->len) + 1,
				       GFP_KERNEL);
			break;
		case WMFW_ABSOLUTE:
			region_name = "Absolute";
			reg = offset;
			break;
		case WMFW_ADSP1_PM:
		case WMFW_ADSP1_DM:
		case WMFW_ADSP2_XM:
		case WMFW_ADSP2_YM:
		case WMFW_ADSP1_ZM:
		case WMFW_HALO_PM_PACKED:
		case WMFW_HALO_XM_PACKED:
		case WMFW_HALO_YM_PACKED:
			mem = wm_adsp_find_region(dsp, type);
			if (!mem) {
				adsp_err(dsp, "No region of type: %x\n", type);
				goto out_fw;
			}

			region_name = wm_adsp_mem_region_name(type);
			reg = dsp->ops->region_to_reg(mem, offset);
			break;
		default:
			adsp_warn(dsp,
				  "%s.%d: Unknown region type %x at %d(%x)\n",
				  file, regions, type, pos, pos);
			break;
		}

		adsp_dbg(dsp, "%s.%d: %d bytes at %d in %s\n", file,
			 regions, le32_to_cpu(region->len), offset,
			 region_name);

		if (le32_to_cpu(region->len) >
		    firmware->size - pos - sizeof(*region)) {
			adsp_err(dsp,
				 "%s.%d: %s region len %d bytes exceeds file length %zu\n",
				 file, regions, region_name,
				 le32_to_cpu(region->len), firmware->size);
			ret = -EINVAL;
			goto out_fw;
		}

		if (text) {
			memcpy(text, region->data, le32_to_cpu(region->len));
			adsp_info(dsp, "%s: %s\n", file, text);
			kfree(text);
			text = NULL;
		}

		if (reg) {
			buf = wm_adsp_buf_alloc(region->data,
						le32_to_cpu(region->len),
						&buf_list);
			if (!buf) {
				adsp_err(dsp, "Out of memory\n");
				ret = -ENOMEM;
				goto out_fw;
			}

			ret = regmap_raw_write_async(regmap, reg, buf->buf,
						     le32_to_cpu(region->len));
			if (ret != 0) {
				adsp_err(dsp,
					"%s.%d: Failed to write %d bytes at %d in %s: %d\n",
					file, regions,
					le32_to_cpu(region->len), offset,
					region_name, ret);
				goto out_fw;
			}
		}

		pos += le32_to_cpu(region->len) + sizeof(*region);
		regions++;
	}

	ret = regmap_async_complete(regmap);
	if (ret != 0) {
		adsp_err(dsp, "Failed to complete async write: %d\n", ret);
		goto out_fw;
	}

	if (pos > firmware->size)
		adsp_warn(dsp, "%s.%d: %zu bytes at end of file\n",
			  file, regions, pos - firmware->size);

	wm_adsp_debugfs_save_wmfwname(dsp, file);

out_fw:
	regmap_async_complete(regmap);
	wm_adsp_buf_free(&buf_list);
	release_firmware(firmware);
	kfree(text);
out:
	kfree(file);

	return ret;
}