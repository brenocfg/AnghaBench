#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
#define  ALT 129 
#define  DEF 128 
 int /*<<< orphan*/  _ALTERNATE ; 
 int /*<<< orphan*/  _DEFAULT ; 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  set_single_persistent_default_layer (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode)
    {
    case DEF:
        if (record->event.pressed)
        {
            print("mode just switched to qwerty and this is a huge string\n");
            set_single_persistent_default_layer(_DEFAULT);
        }
        return false;
        break;
    case ALT:
        if (record->event.pressed)
        {
            set_single_persistent_default_layer(_ALTERNATE);
        }
        return false;
        break;
    }
    return true;
}