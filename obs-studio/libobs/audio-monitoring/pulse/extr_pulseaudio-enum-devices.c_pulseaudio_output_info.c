#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct enum_cb {int /*<<< orphan*/  data; scalar_t__ (* cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ cont; } ;
struct TYPE_3__ {scalar_t__ monitor_of_sink; int /*<<< orphan*/  name; int /*<<< orphan*/  description; } ;
typedef  TYPE_1__ pa_source_info ;
typedef  int /*<<< orphan*/  pa_context ;

/* Variables and functions */
 scalar_t__ PA_INVALID_INDEX ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pulseaudio_signal (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pulseaudio_output_info(pa_context *c, const pa_source_info *i,
				   int eol, void *userdata)
{
	UNUSED_PARAMETER(c);
	if (eol != 0 || i->monitor_of_sink == PA_INVALID_INDEX)
		goto skip;

	struct enum_cb *ecb = (struct enum_cb *)userdata;
	if (ecb->cont)
		ecb->cont = ecb->cb(ecb->data, i->description, i->name);

skip:
	pulseaudio_signal(0);
}