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
typedef  size_t uint32_t ;
struct hvterm_priv {int /*<<< orphan*/  termno; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int hvc_put_chars (int /*<<< orphan*/ ,char const*,int) ; 
 struct hvterm_priv** hvterm_privs ; 

__attribute__((used)) static int hvterm_raw_put_chars(uint32_t vtermno, const char *buf, int count)
{
	struct hvterm_priv *pv = hvterm_privs[vtermno];

	if (WARN_ON(!pv))
		return 0;

	return hvc_put_chars(pv->termno, buf, count);
}