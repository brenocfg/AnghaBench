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
struct env_set {int dummy; } ;
typedef  int /*<<< orphan*/  counter_type ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  counter_format ; 
 int /*<<< orphan*/  openvpn_snprintf (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setenv_str (struct env_set*,char const*,char*) ; 

void
setenv_counter(struct env_set *es, const char *name, counter_type value)
{
    char buf[64];
    openvpn_snprintf(buf, sizeof(buf), counter_format, value);
    setenv_str(es, name, buf);
}