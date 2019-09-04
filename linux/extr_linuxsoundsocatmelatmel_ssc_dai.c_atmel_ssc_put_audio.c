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
 int /*<<< orphan*/  asoc_ssc_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssc_free (struct ssc_device*) ; 
 TYPE_2__* ssc_info ; 

void atmel_ssc_put_audio(int ssc_id)
{
	struct ssc_device *ssc = ssc_info[ssc_id].ssc;

	asoc_ssc_exit(&ssc->pdev->dev);
	ssc_free(ssc);
}