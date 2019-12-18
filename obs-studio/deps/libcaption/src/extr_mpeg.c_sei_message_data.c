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
typedef  int /*<<< orphan*/  uint8_t ;
struct _sei_message_t {int dummy; } ;
typedef  int /*<<< orphan*/  sei_message_t ;

/* Variables and functions */

uint8_t* sei_message_data(sei_message_t* msg) { return ((uint8_t*)msg) + sizeof(struct _sei_message_t); }