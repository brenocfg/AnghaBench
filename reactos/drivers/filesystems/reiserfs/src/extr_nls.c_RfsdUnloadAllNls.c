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
typedef  int /*<<< orphan*/  VOID ;

/* Variables and functions */
 int /*<<< orphan*/  UNLOAD_NLS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit_nls_big5 ; 
 int /*<<< orphan*/  exit_nls_cp1251 ; 
 int /*<<< orphan*/  exit_nls_cp1255 ; 
 int /*<<< orphan*/  exit_nls_cp437 ; 
 int /*<<< orphan*/  exit_nls_cp737 ; 
 int /*<<< orphan*/  exit_nls_cp775 ; 
 int /*<<< orphan*/  exit_nls_cp850 ; 
 int /*<<< orphan*/  exit_nls_cp852 ; 
 int /*<<< orphan*/  exit_nls_cp855 ; 
 int /*<<< orphan*/  exit_nls_cp857 ; 
 int /*<<< orphan*/  exit_nls_cp860 ; 
 int /*<<< orphan*/  exit_nls_cp861 ; 
 int /*<<< orphan*/  exit_nls_cp862 ; 
 int /*<<< orphan*/  exit_nls_cp863 ; 
 int /*<<< orphan*/  exit_nls_cp864 ; 
 int /*<<< orphan*/  exit_nls_cp865 ; 
 int /*<<< orphan*/  exit_nls_cp866 ; 
 int /*<<< orphan*/  exit_nls_cp869 ; 
 int /*<<< orphan*/  exit_nls_cp874 ; 
 int /*<<< orphan*/  exit_nls_cp932 ; 
 int /*<<< orphan*/  exit_nls_cp936 ; 
 int /*<<< orphan*/  exit_nls_cp949 ; 
 int /*<<< orphan*/  exit_nls_cp950 ; 
 int /*<<< orphan*/  exit_nls_euc_jp ; 
 int /*<<< orphan*/  exit_nls_euc_kr ; 
 int /*<<< orphan*/  exit_nls_gb2312 ; 
 int /*<<< orphan*/  exit_nls_iso8859_1 ; 
 int /*<<< orphan*/  exit_nls_iso8859_13 ; 
 int /*<<< orphan*/  exit_nls_iso8859_14 ; 
 int /*<<< orphan*/  exit_nls_iso8859_15 ; 
 int /*<<< orphan*/  exit_nls_iso8859_2 ; 
 int /*<<< orphan*/  exit_nls_iso8859_3 ; 
 int /*<<< orphan*/  exit_nls_iso8859_4 ; 
 int /*<<< orphan*/  exit_nls_iso8859_5 ; 
 int /*<<< orphan*/  exit_nls_iso8859_6 ; 
 int /*<<< orphan*/  exit_nls_iso8859_7 ; 
 int /*<<< orphan*/  exit_nls_iso8859_8 ; 
 int /*<<< orphan*/  exit_nls_iso8859_9 ; 
 int /*<<< orphan*/  exit_nls_koi8_r ; 
 int /*<<< orphan*/  exit_nls_koi8_ru ; 
 int /*<<< orphan*/  exit_nls_koi8_u ; 
 int /*<<< orphan*/  exit_nls_sjis ; 
 int /*<<< orphan*/  exit_nls_tis_620 ; 
 int /*<<< orphan*/  exit_nls_utf8 ; 

VOID
RfsdUnloadAllNls()
{
#ifdef FULL_CODEPAGES_SUPPORT

    UNLOAD_NLS(exit_nls_cp1251);
    UNLOAD_NLS(exit_nls_cp1255);
    UNLOAD_NLS(exit_nls_cp437);
    UNLOAD_NLS(exit_nls_cp737);
    UNLOAD_NLS(exit_nls_cp775);
    UNLOAD_NLS(exit_nls_cp850);
    UNLOAD_NLS(exit_nls_cp852);
    UNLOAD_NLS(exit_nls_cp855);
    UNLOAD_NLS(exit_nls_cp857);
    UNLOAD_NLS(exit_nls_cp860);
    UNLOAD_NLS(exit_nls_cp861);
    UNLOAD_NLS(exit_nls_cp862);
    UNLOAD_NLS(exit_nls_cp863);
    UNLOAD_NLS(exit_nls_cp864);
    UNLOAD_NLS(exit_nls_cp865);
    UNLOAD_NLS(exit_nls_cp866);
    UNLOAD_NLS(exit_nls_cp869);
    UNLOAD_NLS(exit_nls_cp874);
    UNLOAD_NLS(exit_nls_cp949);
    UNLOAD_NLS(exit_nls_cp950);
    UNLOAD_NLS(exit_nls_cp932);
    UNLOAD_NLS(exit_nls_euc_jp);
    UNLOAD_NLS(exit_nls_big5);
    UNLOAD_NLS(exit_nls_euc_kr);
    UNLOAD_NLS(exit_nls_iso8859_1);
    UNLOAD_NLS(exit_nls_iso8859_13);
    UNLOAD_NLS(exit_nls_iso8859_14);
    UNLOAD_NLS(exit_nls_iso8859_15);
    UNLOAD_NLS(exit_nls_iso8859_2);
    UNLOAD_NLS(exit_nls_iso8859_3);
    UNLOAD_NLS(exit_nls_iso8859_4);
    UNLOAD_NLS(exit_nls_iso8859_5);
    UNLOAD_NLS(exit_nls_iso8859_6);
    UNLOAD_NLS(exit_nls_iso8859_7);
    UNLOAD_NLS(exit_nls_iso8859_8);
    UNLOAD_NLS(exit_nls_iso8859_9);
    UNLOAD_NLS(exit_nls_koi8_r);
    UNLOAD_NLS(exit_nls_koi8_ru);
    UNLOAD_NLS(exit_nls_koi8_u);
    UNLOAD_NLS(exit_nls_sjis);
    UNLOAD_NLS(exit_nls_tis_620);

    //
    // Unloading nls of chinese ...
    //

    UNLOAD_NLS(exit_nls_gb2312);
    UNLOAD_NLS(exit_nls_cp936);

#endif //FULL_CODEPAGES_SUPPORT

    //
    // Unloading nls of utf8 ...
    //

    UNLOAD_NLS(exit_nls_utf8);
}