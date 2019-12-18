#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int h_length; } ;
struct dlm_message {TYPE_1__ m_header; } ;

/* Variables and functions */

__attribute__((used)) static int receive_extralen(struct dlm_message *ms)
{
	return (ms->m_header.h_length - sizeof(struct dlm_message));
}