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
struct urb {int /*<<< orphan*/ * setup_packet; } ;

/* Variables and functions */
 int /*<<< orphan*/  SETUP_LEN ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline char mon_bin_get_setup(unsigned char *setupb,
    const struct urb *urb, char ev_type)
{

	if (urb->setup_packet == NULL)
		return 'Z';
	memcpy(setupb, urb->setup_packet, SETUP_LEN);
	return 0;
}