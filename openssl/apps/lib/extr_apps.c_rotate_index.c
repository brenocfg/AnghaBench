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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int BIO_snprintf (char*,int,char*,char const*,...) ; 
 int BSIZE ; 
 scalar_t__ ENOENT ; 
 scalar_t__ ENOTDIR ; 
 int /*<<< orphan*/  bio_err ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ rename (char const*,char const*) ; 
 int strlen (char const*) ; 

int rotate_index(const char *dbfile, const char *new_suffix,
                 const char *old_suffix)
{
    char buf[5][BSIZE];
    int i, j;

    i = strlen(dbfile) + strlen(old_suffix);
    j = strlen(dbfile) + strlen(new_suffix);
    if (i > j)
        j = i;
    if (j + 6 >= BSIZE) {
        BIO_printf(bio_err, "file name too long\n");
        goto err;
    }
#ifndef OPENSSL_SYS_VMS
    j = BIO_snprintf(buf[4], sizeof(buf[4]), "%s.attr", dbfile);
    j = BIO_snprintf(buf[3], sizeof(buf[3]), "%s.attr.%s", dbfile, old_suffix);
    j = BIO_snprintf(buf[2], sizeof(buf[2]), "%s.attr.%s", dbfile, new_suffix);
    j = BIO_snprintf(buf[1], sizeof(buf[1]), "%s.%s", dbfile, old_suffix);
    j = BIO_snprintf(buf[0], sizeof(buf[0]), "%s.%s", dbfile, new_suffix);
#else
    j = BIO_snprintf(buf[4], sizeof(buf[4]), "%s-attr", dbfile);
    j = BIO_snprintf(buf[3], sizeof(buf[3]), "%s-attr-%s", dbfile, old_suffix);
    j = BIO_snprintf(buf[2], sizeof(buf[2]), "%s-attr-%s", dbfile, new_suffix);
    j = BIO_snprintf(buf[1], sizeof(buf[1]), "%s-%s", dbfile, old_suffix);
    j = BIO_snprintf(buf[0], sizeof(buf[0]), "%s-%s", dbfile, new_suffix);
#endif
    if (rename(dbfile, buf[1]) < 0 && errno != ENOENT
#ifdef ENOTDIR
        && errno != ENOTDIR
#endif
        ) {
        BIO_printf(bio_err, "unable to rename %s to %s\n", dbfile, buf[1]);
        perror("reason");
        goto err;
    }
    if (rename(buf[0], dbfile) < 0) {
        BIO_printf(bio_err, "unable to rename %s to %s\n", buf[0], dbfile);
        perror("reason");
        rename(buf[1], dbfile);
        goto err;
    }
    if (rename(buf[4], buf[3]) < 0 && errno != ENOENT
#ifdef ENOTDIR
        && errno != ENOTDIR
#endif
        ) {
        BIO_printf(bio_err, "unable to rename %s to %s\n", buf[4], buf[3]);
        perror("reason");
        rename(dbfile, buf[0]);
        rename(buf[1], dbfile);
        goto err;
    }
    if (rename(buf[2], buf[4]) < 0) {
        BIO_printf(bio_err, "unable to rename %s to %s\n", buf[2], buf[4]);
        perror("reason");
        rename(buf[3], buf[4]);
        rename(dbfile, buf[0]);
        rename(buf[1], dbfile);
        goto err;
    }
    return 1;
 err:
    return 0;
}