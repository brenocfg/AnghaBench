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
struct hvterm_priv {int /*<<< orphan*/  hvsi; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int hvsilib_get_chars (int /*<<< orphan*/ *,char*,int) ; 
 struct hvterm_priv** hvterm_privs ; 

__attribute__((used)) static int hvterm_hvsi_get_chars(uint32_t vtermno, char *buf, int count)
{
	struct hvterm_priv *pv = hvterm_privs[vtermno];

	if (WARN_ON(!pv))
		return 0;

	return hvsilib_get_chars(&pv->hvsi, buf, count);
}