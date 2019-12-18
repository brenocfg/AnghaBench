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
struct nls_table {int dummy; } ;
struct cifs_tcon {int /*<<< orphan*/  treeName; int /*<<< orphan*/  ses; } ;

/* Variables and functions */
 int CIFSTCon (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cifs_tcon*,struct nls_table const*) ; 

__attribute__((used)) static inline int __cifs_reconnect_tcon(const struct nls_table *nlsc,
					struct cifs_tcon *tcon)
{
	return CIFSTCon(0, tcon->ses, tcon->treeName, tcon, nlsc);
}