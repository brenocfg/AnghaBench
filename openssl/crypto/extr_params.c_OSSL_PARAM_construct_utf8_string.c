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
typedef  int /*<<< orphan*/  OSSL_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  OSSL_PARAM_UTF8_STRING ; 
 int /*<<< orphan*/  ossl_param_construct (char const*,int /*<<< orphan*/ ,char*,size_t) ; 
 int strlen (char*) ; 

OSSL_PARAM OSSL_PARAM_construct_utf8_string(const char *key, char *buf,
                                            size_t bsize)
{
    if (buf != NULL && bsize == 0)
        bsize = strlen(buf) + 1;
    return ossl_param_construct(key, OSSL_PARAM_UTF8_STRING, buf, bsize);
}