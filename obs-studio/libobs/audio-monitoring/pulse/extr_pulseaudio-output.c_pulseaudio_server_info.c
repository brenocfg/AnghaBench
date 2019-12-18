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
struct TYPE_3__ {int /*<<< orphan*/  server_version; int /*<<< orphan*/  server_name; } ;
typedef  TYPE_1__ pa_server_info ;
typedef  void pa_context ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (void*) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pulseaudio_signal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pulseaudio_server_info(pa_context *c, const pa_server_info *i,
				   void *userdata)
{
	UNUSED_PARAMETER(c);
	UNUSED_PARAMETER(userdata);

	blog(LOG_INFO, "Server name: '%s %s'", i->server_name,
	     i->server_version);

	pulseaudio_signal(0);
}