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
struct TYPE_3__ {scalar_t__ index; scalar_t__ length; scalar_t__ data; } ;
struct TYPE_4__ {TYPE_1__ buffer; } ;

/* Variables and functions */
 TYPE_2__ I ; 
 scalar_t__ r_str_utf8_charsize (scalar_t__) ; 

__attribute__((used)) static inline void __move_cursor_right() {
	I.buffer.index = I.buffer.index < I.buffer.length
		? I.buffer.index + r_str_utf8_charsize (I.buffer.data + I.buffer.index)
		: I.buffer.length;
}