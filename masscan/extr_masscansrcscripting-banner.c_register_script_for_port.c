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
struct ProtocolParserStream {int dummy; } ;
struct TYPE_2__ {struct ProtocolParserStream** tcp; } ;
struct Banner1 {TYPE_1__ payloads; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  banner_scripting ; 

__attribute__((used)) static void
register_script_for_port(struct Banner1 *b, int port)
{
    LOG(0, "SCRIPTING: using port %d\n", port);
    b->payloads.tcp[port] = (struct ProtocolParserStream *)&banner_scripting;
}