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
struct channel_subsystem {int dummy; } ;

/* Variables and functions */
 struct channel_subsystem** channel_subsystems ; 

__attribute__((used)) static inline struct channel_subsystem *css_by_id(u8 cssid)
{
	return channel_subsystems[0];
}