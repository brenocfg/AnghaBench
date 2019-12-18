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
struct ssc_device {TYPE_1__* pdev; } ;
struct TYPE_4__ {struct ssc_device* ssc; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ssc_device*) ; 
 int PTR_ERR (struct ssc_device*) ; 
 int asoc_ssc_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 TYPE_2__* ssc_info ; 
 struct ssc_device* ssc_request (int) ; 

int atmel_ssc_set_audio(int ssc_id)
{
	struct ssc_device *ssc;
	int ret;

	/* If we can grab the SSC briefly to parent the DAI device off it */
	ssc = ssc_request(ssc_id);
	if (IS_ERR(ssc)) {
		pr_err("Unable to parent ASoC SSC DAI on SSC: %ld\n",
			PTR_ERR(ssc));
		return PTR_ERR(ssc);
	} else {
		ssc_info[ssc_id].ssc = ssc;
	}

	ret = asoc_ssc_init(&ssc->pdev->dev);

	return ret;
}