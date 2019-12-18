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
struct tls_session {TYPE_1__* opt; } ;
struct TYPE_2__ {char const* local_options; } ;

/* Variables and functions */
 char const* ssl_default_options_string ; 

__attribute__((used)) static inline const char *
local_options_string(const struct tls_session *session)
{
#ifdef ENABLE_OCC
    return session->opt->local_options;
#else
    return ssl_default_options_string;
#endif
}