#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sof_topology_token {int dummy; } ;
struct snd_sof_dev {int /*<<< orphan*/  dev; } ;
struct snd_soc_tplg_vendor_array {int size; int type; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SND_SOC_TPLG_TUPLE_TYPE_BOOL 133 
#define  SND_SOC_TPLG_TUPLE_TYPE_BYTE 132 
#define  SND_SOC_TPLG_TUPLE_TYPE_SHORT 131 
#define  SND_SOC_TPLG_TUPLE_TYPE_STRING 130 
#define  SND_SOC_TPLG_TUPLE_TYPE_UUID 129 
#define  SND_SOC_TPLG_TUPLE_TYPE_WORD 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int le32_to_cpu (int) ; 
 struct snd_sof_dev* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  sof_parse_string_tokens (struct snd_soc_component*,void*,struct sof_topology_token const*,int,struct snd_soc_tplg_vendor_array*) ; 
 int /*<<< orphan*/  sof_parse_uuid_tokens (struct snd_soc_component*,void*,struct sof_topology_token const*,int,struct snd_soc_tplg_vendor_array*) ; 
 int /*<<< orphan*/  sof_parse_word_tokens (struct snd_soc_component*,void*,struct sof_topology_token const*,int,struct snd_soc_tplg_vendor_array*) ; 

__attribute__((used)) static int sof_parse_tokens(struct snd_soc_component *scomp,
			    void *object,
			    const struct sof_topology_token *tokens,
			    int count,
			    struct snd_soc_tplg_vendor_array *array,
			    int priv_size)
{
	struct snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	int asize;

	while (priv_size > 0) {
		asize = le32_to_cpu(array->size);

		/* validate asize */
		if (asize < 0) { /* FIXME: A zero-size array makes no sense */
			dev_err(sdev->dev, "error: invalid array size 0x%x\n",
				asize);
			return -EINVAL;
		}

		/* make sure there is enough data before parsing */
		priv_size -= asize;
		if (priv_size < 0) {
			dev_err(sdev->dev, "error: invalid array size 0x%x\n",
				asize);
			return -EINVAL;
		}

		/* call correct parser depending on type */
		switch (le32_to_cpu(array->type)) {
		case SND_SOC_TPLG_TUPLE_TYPE_UUID:
			sof_parse_uuid_tokens(scomp, object, tokens, count,
					      array);
			break;
		case SND_SOC_TPLG_TUPLE_TYPE_STRING:
			sof_parse_string_tokens(scomp, object, tokens, count,
						array);
			break;
		case SND_SOC_TPLG_TUPLE_TYPE_BOOL:
		case SND_SOC_TPLG_TUPLE_TYPE_BYTE:
		case SND_SOC_TPLG_TUPLE_TYPE_WORD:
		case SND_SOC_TPLG_TUPLE_TYPE_SHORT:
			sof_parse_word_tokens(scomp, object, tokens, count,
					      array);
			break;
		default:
			dev_err(sdev->dev, "error: unknown token type %d\n",
				array->type);
			return -EINVAL;
		}

		/* next array */
		array = (struct snd_soc_tplg_vendor_array *)((u8 *)array
			+ asize);
	}
	return 0;
}