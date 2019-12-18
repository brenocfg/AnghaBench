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
 int /*<<< orphan*/  KdPrint (char*) ; 
 int /*<<< orphan*/  LOAD_NLS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_nls_big5 ; 
 int /*<<< orphan*/  init_nls_cp1251 ; 
 int /*<<< orphan*/  init_nls_cp1255 ; 
 int /*<<< orphan*/  init_nls_cp437 ; 
 int /*<<< orphan*/  init_nls_cp737 ; 
 int /*<<< orphan*/  init_nls_cp775 ; 
 int /*<<< orphan*/  init_nls_cp850 ; 
 int /*<<< orphan*/  init_nls_cp852 ; 
 int /*<<< orphan*/  init_nls_cp855 ; 
 int /*<<< orphan*/  init_nls_cp857 ; 
 int /*<<< orphan*/  init_nls_cp860 ; 
 int /*<<< orphan*/  init_nls_cp861 ; 
 int /*<<< orphan*/  init_nls_cp862 ; 
 int /*<<< orphan*/  init_nls_cp863 ; 
 int /*<<< orphan*/  init_nls_cp864 ; 
 int /*<<< orphan*/  init_nls_cp865 ; 
 int /*<<< orphan*/  init_nls_cp866 ; 
 int /*<<< orphan*/  init_nls_cp869 ; 
 int /*<<< orphan*/  init_nls_cp874 ; 
 int /*<<< orphan*/  init_nls_cp932 ; 
 int /*<<< orphan*/  init_nls_cp936 ; 
 int /*<<< orphan*/  init_nls_cp949 ; 
 int /*<<< orphan*/  init_nls_cp950 ; 
 int /*<<< orphan*/  init_nls_euc_jp ; 
 int /*<<< orphan*/  init_nls_euc_kr ; 
 int /*<<< orphan*/  init_nls_gb2312 ; 
 int /*<<< orphan*/  init_nls_iso8859_1 ; 
 int /*<<< orphan*/  init_nls_iso8859_13 ; 
 int /*<<< orphan*/  init_nls_iso8859_14 ; 
 int /*<<< orphan*/  init_nls_iso8859_15 ; 
 int /*<<< orphan*/  init_nls_iso8859_2 ; 
 int /*<<< orphan*/  init_nls_iso8859_3 ; 
 int /*<<< orphan*/  init_nls_iso8859_4 ; 
 int /*<<< orphan*/  init_nls_iso8859_5 ; 
 int /*<<< orphan*/  init_nls_iso8859_6 ; 
 int /*<<< orphan*/  init_nls_iso8859_7 ; 
 int /*<<< orphan*/  init_nls_iso8859_8 ; 
 int /*<<< orphan*/  init_nls_iso8859_9 ; 
 int /*<<< orphan*/  init_nls_koi8_r ; 
 int /*<<< orphan*/  init_nls_koi8_ru ; 
 int /*<<< orphan*/  init_nls_koi8_u ; 
 int /*<<< orphan*/  init_nls_sjis ; 
 int /*<<< orphan*/  init_nls_tis_620 ; 
 int /*<<< orphan*/  init_nls_utf8 ; 
 int /*<<< orphan*/  nls_lock ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tables ; 

int
RfsdLoadAllNls()
{
    int rc;

    tables = NULL;
    spin_lock_init(&nls_lock);

    //
    // Loading nls for utf8 ...
    //

    LOAD_NLS(init_nls_utf8);

#ifdef FULL_CODEPAGES_SUPPORT

    //
    // Loading nls for chinese gb2312 ...
    //

    LOAD_NLS(init_nls_cp936);
    LOAD_NLS(init_nls_gb2312);


    LOAD_NLS(init_nls_cp1251);
    LOAD_NLS(init_nls_cp1255);
    LOAD_NLS(init_nls_cp437);
    LOAD_NLS(init_nls_cp737);
    LOAD_NLS(init_nls_cp775);
    LOAD_NLS(init_nls_cp850);
    LOAD_NLS(init_nls_cp852);
    LOAD_NLS(init_nls_cp855);
    LOAD_NLS(init_nls_cp857);
    LOAD_NLS(init_nls_cp860);
    LOAD_NLS(init_nls_cp861);
    LOAD_NLS(init_nls_cp862);
    LOAD_NLS(init_nls_cp863);
    LOAD_NLS(init_nls_cp864);
    LOAD_NLS(init_nls_cp865);
    LOAD_NLS(init_nls_cp866);
    LOAD_NLS(init_nls_cp869);
    LOAD_NLS(init_nls_cp874);

    //
    // Loading nls for chinese big5
    //

    LOAD_NLS(init_nls_cp950);
    LOAD_NLS(init_nls_big5);

    //
    // Loading jp codepage
    //

    LOAD_NLS(init_nls_cp932);
    LOAD_NLS(init_nls_euc_jp);
    LOAD_NLS(init_nls_sjis);

    //
    // Loading korean nls codepage
    //

    LOAD_NLS(init_nls_cp949);
    LOAD_NLS(init_nls_euc_kr);

    LOAD_NLS(init_nls_iso8859_1);
    LOAD_NLS(init_nls_iso8859_13);
    LOAD_NLS(init_nls_iso8859_14);
    LOAD_NLS(init_nls_iso8859_15);
    LOAD_NLS(init_nls_iso8859_2);
    LOAD_NLS(init_nls_iso8859_3);
    LOAD_NLS(init_nls_iso8859_4);
    LOAD_NLS(init_nls_iso8859_5);
    LOAD_NLS(init_nls_iso8859_6);
    LOAD_NLS(init_nls_iso8859_7);
    LOAD_NLS(init_nls_iso8859_8);
    LOAD_NLS(init_nls_iso8859_9);
    LOAD_NLS(init_nls_koi8_r);
    LOAD_NLS(init_nls_koi8_u);

    LOAD_NLS(init_nls_koi8_ru);
    LOAD_NLS(init_nls_tis_620);

#endif //FULL_CODEPAGES_SUPPORT


    KdPrint(("RfsdLoadAllNls: succeed to load all codepages ...\n"));

errorout:

    return rc;
}