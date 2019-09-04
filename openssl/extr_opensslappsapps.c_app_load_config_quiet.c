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
typedef  int /*<<< orphan*/  CONF ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FORMAT_TEXT ; 
 int /*<<< orphan*/ * app_load_config_bio (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * bio_open_default_quiet (char const*,char,int /*<<< orphan*/ ) ; 

CONF *app_load_config_quiet(const char *filename)
{
    BIO *in;
    CONF *conf;

    in = bio_open_default_quiet(filename, 'r', FORMAT_TEXT);
    if (in == NULL)
        return NULL;

    conf = app_load_config_bio(in, filename);
    BIO_free(in);
    return conf;
}