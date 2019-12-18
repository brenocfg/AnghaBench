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
struct soc_tplg {int req_index; int index; scalar_t__ hdr_pos; scalar_t__ pos; } ;
struct snd_soc_tplg_hdr {int /*<<< orphan*/  type; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 scalar_t__ SND_SOC_TPLG_INDEX_ALL ; 
#define  SND_SOC_TPLG_TYPE_BACKEND_LINK 137 
#define  SND_SOC_TPLG_TYPE_BYTES 136 
#define  SND_SOC_TPLG_TYPE_DAI 135 
#define  SND_SOC_TPLG_TYPE_DAI_LINK 134 
#define  SND_SOC_TPLG_TYPE_DAPM_GRAPH 133 
#define  SND_SOC_TPLG_TYPE_DAPM_WIDGET 132 
#define  SND_SOC_TPLG_TYPE_ENUM 131 
#define  SND_SOC_TPLG_TYPE_MANIFEST 130 
#define  SND_SOC_TPLG_TYPE_MIXER 129 
#define  SND_SOC_TPLG_TYPE_PCM 128 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int soc_tplg_dai_elems_load (struct soc_tplg*,struct snd_soc_tplg_hdr*) ; 
 int soc_tplg_dapm_graph_elems_load (struct soc_tplg*,struct snd_soc_tplg_hdr*) ; 
 int soc_tplg_dapm_widget_elems_load (struct soc_tplg*,struct snd_soc_tplg_hdr*) ; 
 int soc_tplg_kcontrol_elems_load (struct soc_tplg*,struct snd_soc_tplg_hdr*) ; 
 int soc_tplg_link_elems_load (struct soc_tplg*,struct snd_soc_tplg_hdr*) ; 
 int soc_tplg_manifest_load (struct soc_tplg*,struct snd_soc_tplg_hdr*) ; 
 int soc_tplg_pcm_elems_load (struct soc_tplg*,struct snd_soc_tplg_hdr*) ; 
 int soc_tplg_vendor_load (struct soc_tplg*,struct snd_soc_tplg_hdr*) ; 

__attribute__((used)) static int soc_tplg_load_header(struct soc_tplg *tplg,
	struct snd_soc_tplg_hdr *hdr)
{
	tplg->pos = tplg->hdr_pos + sizeof(struct snd_soc_tplg_hdr);

	/* check for matching ID */
	if (le32_to_cpu(hdr->index) != tplg->req_index &&
		tplg->req_index != SND_SOC_TPLG_INDEX_ALL)
		return 0;

	tplg->index = le32_to_cpu(hdr->index);

	switch (le32_to_cpu(hdr->type)) {
	case SND_SOC_TPLG_TYPE_MIXER:
	case SND_SOC_TPLG_TYPE_ENUM:
	case SND_SOC_TPLG_TYPE_BYTES:
		return soc_tplg_kcontrol_elems_load(tplg, hdr);
	case SND_SOC_TPLG_TYPE_DAPM_GRAPH:
		return soc_tplg_dapm_graph_elems_load(tplg, hdr);
	case SND_SOC_TPLG_TYPE_DAPM_WIDGET:
		return soc_tplg_dapm_widget_elems_load(tplg, hdr);
	case SND_SOC_TPLG_TYPE_PCM:
		return soc_tplg_pcm_elems_load(tplg, hdr);
	case SND_SOC_TPLG_TYPE_DAI:
		return soc_tplg_dai_elems_load(tplg, hdr);
	case SND_SOC_TPLG_TYPE_DAI_LINK:
	case SND_SOC_TPLG_TYPE_BACKEND_LINK:
		/* physical link configurations */
		return soc_tplg_link_elems_load(tplg, hdr);
	case SND_SOC_TPLG_TYPE_MANIFEST:
		return soc_tplg_manifest_load(tplg, hdr);
	default:
		/* bespoke vendor data object */
		return soc_tplg_vendor_load(tplg, hdr);
	}

	return 0;
}