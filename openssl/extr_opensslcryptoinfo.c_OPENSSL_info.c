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
 char const* DSO_EXTENSION ; 
 char const* ENGINESDIR ; 
#define  LIST_SEPARATOR_CHAR 134 
 char const* MODULESDIR ; 
 char const* OPENSSLDIR ; 
#define  OPENSSL_INFO_CONFIG_DIR 133 
#define  OPENSSL_INFO_DIR_FILENAME_SEPARATOR 132 
#define  OPENSSL_INFO_DSO_EXTENSION 131 
#define  OPENSSL_INFO_ENGINES_DIR 130 
#define  OPENSSL_INFO_LIST_SEPARATOR 129 
#define  OPENSSL_INFO_MODULES_DIR 128 

const char *OPENSSL_info(int t)
{
    switch (t) {
    case OPENSSL_INFO_CONFIG_DIR:
        return OPENSSLDIR;
    case OPENSSL_INFO_ENGINES_DIR:
        return ENGINESDIR;
    case OPENSSL_INFO_MODULES_DIR:
        return MODULESDIR;
    case OPENSSL_INFO_DSO_EXTENSION:
        return DSO_EXTENSION;
    case OPENSSL_INFO_DIR_FILENAME_SEPARATOR:
#if defined(_WIN32)
        return "\\";
#elif defined(__VMS)
        return "";
#else  /* Assume POSIX */
        return "/";
#endif
    case OPENSSL_INFO_LIST_SEPARATOR:
        {
            static const char list_sep[] = { LIST_SEPARATOR_CHAR, '\0' };
            return list_sep;
        }
    default:
        break;
    }
    /* Not an error */
    return NULL;
}