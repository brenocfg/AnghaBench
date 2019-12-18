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
struct gc_arena {int dummy; } ;
typedef  int /*<<< orphan*/  openvpn_x509_cert_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int M_ERRNO ; 
 int M_NONFATAL ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  msg (int,char*,...) ; 
 char* platform_create_temp_file (char const*,char*,struct gc_arena*) ; 
 int /*<<< orphan*/  platform_unlink (char const*) ; 
 scalar_t__ x509_write_pem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
verify_cert_export_cert(openvpn_x509_cert_t *peercert, const char *tmp_dir, struct gc_arena *gc)
{
    FILE *peercert_file;
    const char *peercert_filename = "";

    /* create tmp file to store peer cert */
    if (!tmp_dir
        || !(peercert_filename = platform_create_temp_file(tmp_dir, "pcf", gc)))
    {
        msg(M_NONFATAL, "Failed to create peer cert file");
        return NULL;
    }

    /* write peer-cert in tmp-file */
    peercert_file = fopen(peercert_filename, "w+");
    if (!peercert_file)
    {
        msg(M_NONFATAL|M_ERRNO, "Failed to open temporary file: %s",
            peercert_filename);
        return NULL;
    }

    if (SUCCESS != x509_write_pem(peercert_file, peercert))
    {
        msg(M_NONFATAL, "Error writing PEM file containing certificate");
        (void) platform_unlink(peercert_filename);
        peercert_filename = NULL;
    }

    fclose(peercert_file);
    return peercert_filename;
}