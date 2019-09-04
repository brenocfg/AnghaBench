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
struct hdspm {int io_type; scalar_t__ tco; } ;

/* Variables and functions */
#define  AIO 129 
 int /*<<< orphan*/  HDSPM_RD_STATUS_2 ; 
#define  RayDAT 128 
 int hdspm_read (struct hdspm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdspm_get_sync_in_sample_rate(struct hdspm *hdspm)
{
	int status;

	if (hdspm->tco) {
		switch (hdspm->io_type) {
		case RayDAT:
		case AIO:
			status = hdspm_read(hdspm, HDSPM_RD_STATUS_2);
			return (status >> 12) & 0xF;
			break;
		default:
			break;
		}
	}

	return 0;
}