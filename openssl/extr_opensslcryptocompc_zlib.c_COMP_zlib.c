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
typedef  int /*<<< orphan*/  COMP_METHOD ;

/* Variables and functions */
 int /*<<< orphan*/  zlib_method_nozlib ; 

COMP_METHOD *COMP_zlib(void)
{
    COMP_METHOD *meth = &zlib_method_nozlib;

#ifdef ZLIB_SHARED
    /* LIBZ may be externally defined, and we should respect that value */
# ifndef LIBZ
#  if defined(OPENSSL_SYS_WINDOWS) || defined(OPENSSL_SYS_WIN32)
#   define LIBZ "ZLIB1"
#  elif defined(OPENSSL_SYS_VMS)
#   define LIBZ "LIBZ"
#  else
#   define LIBZ "z"
#  endif
# endif

    if (!zlib_loaded) {
        zlib_dso = DSO_load(NULL, LIBZ, NULL, 0);
        if (zlib_dso != NULL) {
            p_compress = (compress_ft) DSO_bind_func(zlib_dso, "compress");
            p_inflateEnd
                = (inflateEnd_ft) DSO_bind_func(zlib_dso, "inflateEnd");
            p_inflate = (inflate_ft) DSO_bind_func(zlib_dso, "inflate");
            p_inflateInit_
                = (inflateInit__ft) DSO_bind_func(zlib_dso, "inflateInit_");
            p_deflateEnd
                = (deflateEnd_ft) DSO_bind_func(zlib_dso, "deflateEnd");
            p_deflate = (deflate_ft) DSO_bind_func(zlib_dso, "deflate");
            p_deflateInit_
                = (deflateInit__ft) DSO_bind_func(zlib_dso, "deflateInit_");
            p_zError = (zError__ft) DSO_bind_func(zlib_dso, "zError");

            if (p_compress && p_inflateEnd && p_inflate
                && p_inflateInit_ && p_deflateEnd
                && p_deflate && p_deflateInit_ && p_zError)
                zlib_loaded++;

            if (!OPENSSL_init_crypto(OPENSSL_INIT_ZLIB, NULL)) {
                comp_zlib_cleanup_int();
                return meth;
            }
            if (zlib_loaded)
                meth = &zlib_stateful_method;
        }
    }
#endif
#if defined(ZLIB)
    meth = &zlib_stateful_method;
#endif

    return meth;
}