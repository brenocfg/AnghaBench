#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct snd_kcontrol_new {int access; int /*<<< orphan*/  get; int /*<<< orphan*/  info; int /*<<< orphan*/  put; int /*<<< orphan*/  private_value; } ;
struct clk_cache {int has_local; int count; TYPE_1__* s; } ;
struct snd_card_asihpi {struct clk_cache cc; struct snd_card* card; } ;
struct snd_card {int dummy; } ;
struct hpi_control {int /*<<< orphan*/  h_control; } ;
struct TYPE_2__ {size_t source; int index; void* name; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t HPI_SAMPLECLOCK_SOURCE_AESEBU_INPUT ; 
 int HPI_SAMPLECLOCK_SOURCE_LAST ; 
 size_t HPI_SAMPLECLOCK_SOURCE_LOCAL ; 
 int SNDRV_CTL_ELEM_ACCESS_READ ; 
 void* SNDRV_CTL_ELEM_ACCESS_READWRITE ; 
 int SNDRV_CTL_ELEM_ACCESS_VOLATILE ; 
 int /*<<< orphan*/  asihpi_ctl_init (struct snd_kcontrol_new*,struct hpi_control*,char*) ; 
 int ctl_add (struct snd_card*,struct snd_kcontrol_new*,struct snd_card_asihpi*) ; 
 scalar_t__ hpi_sample_clock_query_source (int /*<<< orphan*/ ,int,size_t*) ; 
 scalar_t__ hpi_sample_clock_query_source_index (int /*<<< orphan*/ ,int,size_t,size_t*) ; 
 void** sampleclock_sources ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_asihpi_clklocal_get ; 
 int /*<<< orphan*/  snd_asihpi_clklocal_info ; 
 int /*<<< orphan*/  snd_asihpi_clklocal_put ; 
 int /*<<< orphan*/  snd_asihpi_clkrate_get ; 
 int /*<<< orphan*/  snd_asihpi_clkrate_info ; 
 int /*<<< orphan*/  snd_asihpi_clksrc_get ; 
 int /*<<< orphan*/  snd_asihpi_clksrc_info ; 
 int /*<<< orphan*/  snd_asihpi_clksrc_put ; 

__attribute__((used)) static int snd_asihpi_sampleclock_add(struct snd_card_asihpi *asihpi,
				      struct hpi_control *hpi_ctl)
{
	struct snd_card *card;
	struct snd_kcontrol_new snd_control;

	struct clk_cache *clkcache;
	u32 hSC =  hpi_ctl->h_control;
	int has_aes_in = 0;
	int i, j;
	u16 source;

	if (snd_BUG_ON(!asihpi))
		return -EINVAL;
	card = asihpi->card;
	clkcache = &asihpi->cc;
	snd_control.private_value = hpi_ctl->h_control;

	clkcache->has_local = 0;

	for (i = 0; i <= HPI_SAMPLECLOCK_SOURCE_LAST; i++) {
		if  (hpi_sample_clock_query_source(hSC,
				i, &source))
			break;
		clkcache->s[i].source = source;
		clkcache->s[i].index = 0;
		clkcache->s[i].name = sampleclock_sources[source];
		if (source == HPI_SAMPLECLOCK_SOURCE_AESEBU_INPUT)
			has_aes_in = 1;
		if (source == HPI_SAMPLECLOCK_SOURCE_LOCAL)
			clkcache->has_local = 1;
	}
	if (has_aes_in)
		/* already will have picked up index 0 above */
		for (j = 1; j < 8; j++) {
			if (hpi_sample_clock_query_source_index(hSC,
				j, HPI_SAMPLECLOCK_SOURCE_AESEBU_INPUT,
				&source))
				break;
			clkcache->s[i].source =
				HPI_SAMPLECLOCK_SOURCE_AESEBU_INPUT;
			clkcache->s[i].index = j;
			clkcache->s[i].name = sampleclock_sources[
					j+HPI_SAMPLECLOCK_SOURCE_LAST];
			i++;
		}
	clkcache->count = i;

	asihpi_ctl_init(&snd_control, hpi_ctl, "Source");
	snd_control.access = SNDRV_CTL_ELEM_ACCESS_READWRITE ;
	snd_control.info = snd_asihpi_clksrc_info;
	snd_control.get = snd_asihpi_clksrc_get;
	snd_control.put = snd_asihpi_clksrc_put;
	if (ctl_add(card, &snd_control, asihpi) < 0)
		return -EINVAL;


	if (clkcache->has_local) {
		asihpi_ctl_init(&snd_control, hpi_ctl, "Localrate");
		snd_control.access = SNDRV_CTL_ELEM_ACCESS_READWRITE ;
		snd_control.info = snd_asihpi_clklocal_info;
		snd_control.get = snd_asihpi_clklocal_get;
		snd_control.put = snd_asihpi_clklocal_put;


		if (ctl_add(card, &snd_control, asihpi) < 0)
			return -EINVAL;
	}

	asihpi_ctl_init(&snd_control, hpi_ctl, "Rate");
	snd_control.access =
	    SNDRV_CTL_ELEM_ACCESS_VOLATILE | SNDRV_CTL_ELEM_ACCESS_READ;
	snd_control.info = snd_asihpi_clkrate_info;
	snd_control.get = snd_asihpi_clkrate_get;

	return ctl_add(card, &snd_control, asihpi);
}