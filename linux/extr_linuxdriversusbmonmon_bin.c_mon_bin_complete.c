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
struct urb {int dummy; } ;
struct mon_reader_bin {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mon_bin_event (struct mon_reader_bin*,struct urb*,char,int) ; 

__attribute__((used)) static void mon_bin_complete(void *data, struct urb *urb, int status)
{
	struct mon_reader_bin *rp = data;
	mon_bin_event(rp, urb, 'C', status);
}