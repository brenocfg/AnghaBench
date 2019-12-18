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

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,char const*) ; 
 int NID_undef ; 
 int OBJ_txt2nid (char const*) ; 
 int /*<<< orphan*/  bio_err ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int set_pbe(int *ppbe, const char *str)
{
    if (!str)
        return 0;
    if (strcmp(str, "NONE") == 0) {
        *ppbe = -1;
        return 1;
    }
    *ppbe = OBJ_txt2nid(str);
    if (*ppbe == NID_undef) {
        BIO_printf(bio_err, "Unknown PBE algorithm %s\n", str);
        return 0;
    }
    return 1;
}