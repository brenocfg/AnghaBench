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
struct soc_tplg {int /*<<< orphan*/  dev; } ;
struct snd_soc_tplg_stream {int dummy; } ;
struct snd_soc_tplg_link_config_v4 {int /*<<< orphan*/ * stream; int /*<<< orphan*/  num_streams; int /*<<< orphan*/  id; } ;
struct snd_soc_tplg_link_config {int /*<<< orphan*/ * stream; int /*<<< orphan*/  num_streams; int /*<<< orphan*/  id; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 struct snd_soc_tplg_link_config* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int link_new_ver(struct soc_tplg *tplg,
			struct snd_soc_tplg_link_config *src,
			struct snd_soc_tplg_link_config **link)
{
	struct snd_soc_tplg_link_config *dest;
	struct snd_soc_tplg_link_config_v4 *src_v4;
	int i;

	*link = NULL;

	if (le32_to_cpu(src->size) !=
	    sizeof(struct snd_soc_tplg_link_config_v4)) {
		dev_err(tplg->dev, "ASoC: invalid physical link config size\n");
		return -EINVAL;
	}

	dev_warn(tplg->dev, "ASoC: old version of physical link config\n");

	src_v4 = (struct snd_soc_tplg_link_config_v4 *)src;
	dest = kzalloc(sizeof(*dest), GFP_KERNEL);
	if (!dest)
		return -ENOMEM;

	dest->size = cpu_to_le32(sizeof(*dest));
	dest->id = src_v4->id;
	dest->num_streams = src_v4->num_streams;
	for (i = 0; i < le32_to_cpu(dest->num_streams); i++)
		memcpy(&dest->stream[i], &src_v4->stream[i],
		       sizeof(struct snd_soc_tplg_stream));

	*link = dest;
	return 0;
}