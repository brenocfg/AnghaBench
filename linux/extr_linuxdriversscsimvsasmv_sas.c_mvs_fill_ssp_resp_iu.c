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
struct ssp_response_iu {int datapres; int sense_data_len; int status; int /*<<< orphan*/  sense_data; scalar_t__ response_data_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  mvs_set_sense (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvs_fill_ssp_resp_iu(struct ssp_response_iu *iu,
				u8 key, u8 asc, u8 asc_q)
{
	iu->datapres = 2;
	iu->response_data_len = 0;
	iu->sense_data_len = 17;
	iu->status = 02;
	mvs_set_sense(iu->sense_data, 17, 0,
			key, asc, asc_q);
}