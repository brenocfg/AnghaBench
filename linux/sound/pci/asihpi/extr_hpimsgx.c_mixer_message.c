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
struct hpi_response {int dummy; } ;
struct hpi_message {int function; } ;

/* Variables and functions */
#define  HPI_MIXER_CLOSE 129 
#define  HPI_MIXER_OPEN 128 
 int /*<<< orphan*/  hw_entry_point (struct hpi_message*,struct hpi_response*) ; 
 int /*<<< orphan*/  mixer_close (struct hpi_message*,struct hpi_response*) ; 
 int /*<<< orphan*/  mixer_open (struct hpi_message*,struct hpi_response*) ; 

__attribute__((used)) static void mixer_message(struct hpi_message *phm, struct hpi_response *phr)
{
	switch (phm->function) {
	case HPI_MIXER_OPEN:
		mixer_open(phm, phr);
		break;
	case HPI_MIXER_CLOSE:
		mixer_close(phm, phr);
		break;
	default:
		hw_entry_point(phm, phr);
		break;
	}
}