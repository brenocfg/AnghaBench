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
 char const* DATE ; 
#define  OPENSSL_BUILT_ON 136 
#define  OPENSSL_CFLAGS 135 
#define  OPENSSL_DIR 134 
#define  OPENSSL_ENGINES_DIR 133 
 char const* OPENSSL_FULL_VERSION_STR ; 
#define  OPENSSL_FULL_VERSION_STRING 132 
#define  OPENSSL_MODULES_DIR 131 
#define  OPENSSL_PLATFORM 130 
#define  OPENSSL_VERSION 129 
 char const* OPENSSL_VERSION_STR ; 
#define  OPENSSL_VERSION_STRING 128 
 char const* OPENSSL_VERSION_TEXT ; 
 char const* PLATFORM ; 
 char const* compiler_flags ; 

const char *OpenSSL_version(int t)
{
    switch (t) {
    case OPENSSL_VERSION:
        return OPENSSL_VERSION_TEXT;
    case OPENSSL_VERSION_STRING:
        return OPENSSL_VERSION_STR;
    case OPENSSL_FULL_VERSION_STRING:
        return OPENSSL_FULL_VERSION_STR;
    case OPENSSL_BUILT_ON:
        return DATE;
    case OPENSSL_CFLAGS:
        return compiler_flags;
    case OPENSSL_PLATFORM:
        return PLATFORM;
    case OPENSSL_DIR:
#ifdef OPENSSLDIR
        return "OPENSSLDIR: \"" OPENSSLDIR "\"";
#else
        return "OPENSSLDIR: N/A";
#endif
    case OPENSSL_ENGINES_DIR:
#ifdef ENGINESDIR
        return "ENGINESDIR: \"" ENGINESDIR "\"";
#else
        return "ENGINESDIR: N/A";
#endif
    case OPENSSL_MODULES_DIR:
#ifdef MODULESDIR
        return "MODULESDIR: \"" MODULESDIR "\"";
#else
        return "MODULESDIR: N/A";
#endif
    }
    return "not available";
}