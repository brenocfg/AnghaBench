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
struct TYPE_2__ {int /*<<< orphan*/  db; } ;

/* Variables and functions */
 char* PQsslAttribute (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PQsslInUse (int /*<<< orphan*/ ) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  printf (char*,char const*,char const*,char const*,char*) ; 
 TYPE_1__ pset ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static void
printSSLInfo(void)
{
	const char *protocol;
	const char *cipher;
	const char *bits;
	const char *compression;

	if (!PQsslInUse(pset.db))
		return;					/* no SSL */

	protocol = PQsslAttribute(pset.db, "protocol");
	cipher = PQsslAttribute(pset.db, "cipher");
	bits = PQsslAttribute(pset.db, "key_bits");
	compression = PQsslAttribute(pset.db, "compression");

	printf(_("SSL connection (protocol: %s, cipher: %s, bits: %s, compression: %s)\n"),
		   protocol ? protocol : _("unknown"),
		   cipher ? cipher : _("unknown"),
		   bits ? bits : _("unknown"),
		   (compression && strcmp(compression, "off") != 0) ? _("on") : _("off"));
}