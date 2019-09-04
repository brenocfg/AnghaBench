#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct f_audio {int /*<<< orphan*/  cs; } ;
struct TYPE_6__ {int /*<<< orphan*/  control; int /*<<< orphan*/  list; } ;
struct TYPE_5__ {int /*<<< orphan*/  list; } ;
struct TYPE_4__ {int* data; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 size_t UAC__CUR ; 
 size_t UAC__MAX ; 
 size_t UAC__MIN ; 
 size_t UAC__RES ; 
 TYPE_3__ feature_unit ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__ mute_control ; 
 TYPE_1__ volume_control ; 

__attribute__((used)) static int control_selector_init(struct f_audio *audio)
{
	INIT_LIST_HEAD(&audio->cs);
	list_add(&feature_unit.list, &audio->cs);

	INIT_LIST_HEAD(&feature_unit.control);
	list_add(&mute_control.list, &feature_unit.control);
	list_add(&volume_control.list, &feature_unit.control);

	volume_control.data[UAC__CUR] = 0xffc0;
	volume_control.data[UAC__MIN] = 0xe3a0;
	volume_control.data[UAC__MAX] = 0xfff0;
	volume_control.data[UAC__RES] = 0x0030;

	return 0;
}