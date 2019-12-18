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
struct tls_session {int /*<<< orphan*/  untrusted_addr; TYPE_1__* opt; } ;
struct TYPE_2__ {int /*<<< orphan*/  es; } ;

/* Variables and functions */
 int /*<<< orphan*/  SA_IP_PORT ; 
 int /*<<< orphan*/  setenv_link_socket_actual (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
setenv_untrusted(struct tls_session *session)
{
    setenv_link_socket_actual(session->opt->es, "untrusted", &session->untrusted_addr, SA_IP_PORT);
}