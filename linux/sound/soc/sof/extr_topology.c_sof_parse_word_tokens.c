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
typedef  size_t u32 ;
struct sof_topology_token {scalar_t__ type; int token; size_t offset; int /*<<< orphan*/  size; int /*<<< orphan*/  (* get_token ) (struct snd_soc_tplg_vendor_value_elem*,void*,size_t,int /*<<< orphan*/ ) ;} ;
struct sof_ipc_dai_dmic_pdm_ctrl {int dummy; } ;
struct snd_sof_dev {size_t* private; int /*<<< orphan*/  dev; } ;
struct snd_soc_tplg_vendor_value_elem {int /*<<< orphan*/  token; } ;
struct snd_soc_tplg_vendor_array {struct snd_soc_tplg_vendor_value_elem* value; int /*<<< orphan*/  num_elems; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 scalar_t__ SND_SOC_TPLG_TUPLE_TYPE_BOOL ; 
 scalar_t__ SND_SOC_TPLG_TUPLE_TYPE_BYTE ; 
 scalar_t__ SND_SOC_TPLG_TUPLE_TYPE_SHORT ; 
 scalar_t__ SND_SOC_TPLG_TUPLE_TYPE_WORD ; 
#define  SOF_TKN_INTEL_DMIC_PDM_CLK_EDGE 134 
#define  SOF_TKN_INTEL_DMIC_PDM_CTRL_ID 133 
#define  SOF_TKN_INTEL_DMIC_PDM_MIC_A_Enable 132 
#define  SOF_TKN_INTEL_DMIC_PDM_MIC_B_Enable 131 
#define  SOF_TKN_INTEL_DMIC_PDM_POLARITY_A 130 
#define  SOF_TKN_INTEL_DMIC_PDM_POLARITY_B 129 
#define  SOF_TKN_INTEL_DMIC_PDM_SKEW 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct snd_sof_dev* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  stub1 (struct snd_soc_tplg_vendor_value_elem*,void*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sof_parse_word_tokens(struct snd_soc_component *scomp,
				  void *object,
				  const struct sof_topology_token *tokens,
				  int count,
				  struct snd_soc_tplg_vendor_array *array)
{
	struct snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	struct snd_soc_tplg_vendor_value_elem *elem;
	size_t size = sizeof(struct sof_ipc_dai_dmic_pdm_ctrl);
	int i, j;
	u32 offset;
	u32 *index = NULL;

	/* parse element by element */
	for (i = 0; i < le32_to_cpu(array->num_elems); i++) {
		elem = &array->value[i];

		/* search for token */
		for (j = 0; j < count; j++) {
			/* match token type */
			if (!(tokens[j].type == SND_SOC_TPLG_TUPLE_TYPE_WORD ||
			      tokens[j].type == SND_SOC_TPLG_TUPLE_TYPE_SHORT ||
			      tokens[j].type == SND_SOC_TPLG_TUPLE_TYPE_BYTE ||
			      tokens[j].type == SND_SOC_TPLG_TUPLE_TYPE_BOOL))
				continue;

			/* match token id */
			if (tokens[j].token != le32_to_cpu(elem->token))
				continue;

			/* pdm config array index */
			if (sdev->private)
				index = sdev->private;

			/* matched - determine offset */
			switch (tokens[j].token) {
			case SOF_TKN_INTEL_DMIC_PDM_CTRL_ID:

				/* inc number of pdm array index */
				if (index)
					(*index)++;
				/* fallthrough */
			case SOF_TKN_INTEL_DMIC_PDM_MIC_A_Enable:
			case SOF_TKN_INTEL_DMIC_PDM_MIC_B_Enable:
			case SOF_TKN_INTEL_DMIC_PDM_POLARITY_A:
			case SOF_TKN_INTEL_DMIC_PDM_POLARITY_B:
			case SOF_TKN_INTEL_DMIC_PDM_CLK_EDGE:
			case SOF_TKN_INTEL_DMIC_PDM_SKEW:

				/* check if array index is valid */
				if (!index || *index == 0) {
					dev_err(sdev->dev,
						"error: invalid array offset\n");
					continue;
				} else {
					/* offset within the pdm config array */
					offset = size * (*index - 1);
				}
				break;
			default:
				offset = 0;
				break;
			}

			/* load token */
			tokens[j].get_token(elem, object,
					    offset + tokens[j].offset,
					    tokens[j].size);
		}
	}
}