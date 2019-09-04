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
struct _sei_message_t {int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  sei_msgtype_t ;
typedef  int /*<<< orphan*/  sei_message_t ;

/* Variables and functions */

sei_msgtype_t sei_message_type(sei_message_t* msg) { return ((struct _sei_message_t*)msg)->type; }