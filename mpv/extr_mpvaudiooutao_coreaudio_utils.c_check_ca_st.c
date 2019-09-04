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
struct ao {int /*<<< orphan*/  log; } ;
typedef  scalar_t__ OSStatus ;

/* Variables and functions */
 int /*<<< orphan*/  mp_msg (int /*<<< orphan*/ ,int,char*,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mp_tag_str (scalar_t__) ; 
 scalar_t__ noErr ; 

bool check_ca_st(struct ao *ao, int level, OSStatus code, const char *message)
{
    if (code == noErr) return true;

    mp_msg(ao->log, level, "%s (%s/%d)\n", message, mp_tag_str(code), (int)code);

    return false;
}