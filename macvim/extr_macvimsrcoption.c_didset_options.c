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
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bkc_flags ; 
 int /*<<< orphan*/  dy_flags ; 
 int /*<<< orphan*/  init_chartab () ; 
 int /*<<< orphan*/  opt_strings_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_bkc ; 
 int /*<<< orphan*/  p_bkc_values ; 
 int /*<<< orphan*/  p_dy ; 
 int /*<<< orphan*/  p_dy_values ; 

__attribute__((used)) static void
didset_options()
{
    /* initialize the table for 'iskeyword' et.al. */
    (void)init_chartab();

#ifdef FEAT_MBYTE
    (void)opt_strings_flags(p_cmp, p_cmp_values, &cmp_flags, TRUE);
#endif
    (void)opt_strings_flags(p_bkc, p_bkc_values, &bkc_flags, TRUE);
#ifdef FEAT_SESSION
    (void)opt_strings_flags(p_ssop, p_ssop_values, &ssop_flags, TRUE);
    (void)opt_strings_flags(p_vop, p_ssop_values, &vop_flags, TRUE);
#endif
#ifdef FEAT_FOLDING
    (void)opt_strings_flags(p_fdo, p_fdo_values, &fdo_flags, TRUE);
#endif
#ifdef FEAT_FULLSCREEN
    (void)check_fuoptions(p_fuoptions, &fuoptions_flags, 
            &fuoptions_bgcolor);
#endif
    (void)opt_strings_flags(p_dy, p_dy_values, &dy_flags, TRUE);
#ifdef FEAT_VIRTUALEDIT
    (void)opt_strings_flags(p_ve, p_ve_values, &ve_flags, TRUE);
#endif
#if defined(FEAT_MOUSE) && (defined(UNIX) || defined(VMS))
    (void)opt_strings_flags(p_ttym, p_ttym_values, &ttym_flags, FALSE);
#endif
#ifdef FEAT_SPELL
    (void)spell_check_msm();
    (void)spell_check_sps();
    (void)compile_cap_prog(curwin->w_s);
#endif
#if defined(FEAT_TOOLBAR) && !defined(FEAT_GUI_W32)
    (void)opt_strings_flags(p_toolbar, p_toolbar_values, &toolbar_flags, TRUE);
#endif
#if defined(FEAT_TOOLBAR) && (defined(FEAT_GUI_GTK) || defined(FEAT_GUI_MACVIM))
    (void)opt_strings_flags(p_tbis, p_tbis_values, &tbis_flags, FALSE);
#endif
#ifdef FEAT_CMDWIN
    /* set cedit_key */
    (void)check_cedit();
#endif
#ifdef FEAT_LINEBREAK
    briopt_check();
#endif
}