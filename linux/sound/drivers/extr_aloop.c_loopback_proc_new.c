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
struct loopback {int /*<<< orphan*/  card; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  print_cable_info ; 
 int snd_card_ro_proc_new (int /*<<< orphan*/ ,char*,struct loopback*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int loopback_proc_new(struct loopback *loopback, int cidx)
{
	char name[32];

	snprintf(name, sizeof(name), "cable#%d", cidx);
	return snd_card_ro_proc_new(loopback->card, name, loopback,
				    print_cable_info);
}