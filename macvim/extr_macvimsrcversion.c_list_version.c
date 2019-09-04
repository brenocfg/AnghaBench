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
 int /*<<< orphan*/  MSG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG_PUTS (char*) ; 
 char* _ (char*) ; 
 char** extra_patches ; 
 int* included_patches ; 
 int /*<<< orphan*/  list_features () ; 
 int /*<<< orphan*/  longVersion ; 
 int /*<<< orphan*/  msg_outnum (long) ; 
 int /*<<< orphan*/  version_msg (char*) ; 

void
list_version()
{
    int		i;
    int		first;
    char	*s = "";

    /*
     * When adding features here, don't forget to update the list of
     * internal variables in eval.c!
     */
    MSG(longVersion);
#ifdef WIN3264
# ifdef FEAT_GUI_W32
#  if defined(_MSC_VER) && (_MSC_VER <= 1010)
    /* Only MS VC 4.1 and earlier can do Win32s */
    MSG_PUTS(_("\nMS-Windows 16/32-bit GUI version"));
#  else
#   ifdef _WIN64
    MSG_PUTS(_("\nMS-Windows 64-bit GUI version"));
#   else
    MSG_PUTS(_("\nMS-Windows 32-bit GUI version"));
#   endif
#  endif
    if (gui_is_win32s())
	MSG_PUTS(_(" in Win32s mode"));
# ifdef FEAT_OLE
    MSG_PUTS(_(" with OLE support"));
# endif
# else
#  ifdef _WIN64
    MSG_PUTS(_("\nMS-Windows 64-bit console version"));
#  else
    MSG_PUTS(_("\nMS-Windows 32-bit console version"));
#  endif
# endif
#endif
#ifdef WIN16
    MSG_PUTS(_("\nMS-Windows 16-bit version"));
#endif
#ifdef MSDOS
# ifdef DJGPP
    MSG_PUTS(_("\n32-bit MS-DOS version"));
# else
    MSG_PUTS(_("\n16-bit MS-DOS version"));
# endif
#endif
#ifdef MACOS
# ifdef MACOS_X
#  ifdef MACOS_X_UNIX
    MSG_PUTS(_("\nMacOS X (unix) version"));
#  else
    MSG_PUTS(_("\nMacOS X version"));
#  endif
#else
    MSG_PUTS(_("\nMacOS version"));
# endif
#endif

#ifdef VMS
    MSG_PUTS(_("\nOpenVMS version"));
# ifdef HAVE_PATHDEF
    if (*compiled_arch != NUL)
    {
	MSG_PUTS(" - ");
	MSG_PUTS(compiled_arch);
    }
# endif

#endif

    /* Print the list of patch numbers if there is at least one. */
    /* Print a range when patches are consecutive: "1-10, 12, 15-40, 42-45" */
    if (included_patches[0] != 0)
    {
	MSG_PUTS(_("\nIncluded patches: "));
	first = -1;
	/* find last one */
	for (i = 0; included_patches[i] != 0; ++i)
	    ;
	while (--i >= 0)
	{
	    if (first < 0)
		first = included_patches[i];
	    if (i == 0 || included_patches[i - 1] != included_patches[i] + 1)
	    {
		MSG_PUTS(s);
		s = ", ";
		msg_outnum((long)first);
		if (first != included_patches[i])
		{
		    MSG_PUTS("-");
		    msg_outnum((long)included_patches[i]);
		}
		first = -1;
	    }
	}
    }

    /* Print the list of extra patch descriptions if there is at least one. */
    if (extra_patches[0] != NULL)
    {
	MSG_PUTS(_("\nExtra patches: "));
	s = "";
	for (i = 0; extra_patches[i] != NULL; ++i)
	{
	    MSG_PUTS(s);
	    s = ", ";
	    MSG_PUTS(extra_patches[i]);
	}
    }

#ifdef MODIFIED_BY
    MSG_PUTS("\n");
    MSG_PUTS(_("Modified by "));
    MSG_PUTS(MODIFIED_BY);
#endif

#ifdef HAVE_PATHDEF
    if (*compiled_user != NUL || *compiled_sys != NUL)
    {
	MSG_PUTS(_("\nCompiled "));
	if (*compiled_user != NUL)
	{
	    MSG_PUTS(_("by "));
	    MSG_PUTS(compiled_user);
	}
	if (*compiled_sys != NUL)
	{
	    MSG_PUTS("@");
	    MSG_PUTS(compiled_sys);
	}
    }
#endif

#ifdef FEAT_HUGE
    MSG_PUTS(_("\nHuge version "));
#else
# ifdef FEAT_BIG
    MSG_PUTS(_("\nBig version "));
# else
#  ifdef FEAT_NORMAL
    MSG_PUTS(_("\nNormal version "));
#  else
#   ifdef FEAT_SMALL
    MSG_PUTS(_("\nSmall version "));
#   else
    MSG_PUTS(_("\nTiny version "));
#   endif
#  endif
# endif
#endif
#ifndef FEAT_GUI
    MSG_PUTS(_("without GUI."));
#else
# ifdef FEAT_GUI_GTK
#  ifdef FEAT_GUI_GNOME
    MSG_PUTS(_("with GTK2-GNOME GUI."));
#  else
    MSG_PUTS(_("with GTK2 GUI."));
#  endif
# else
#  ifdef FEAT_GUI_MOTIF
    MSG_PUTS(_("with X11-Motif GUI."));
#  else
#   ifdef FEAT_GUI_ATHENA
#    ifdef FEAT_GUI_NEXTAW
    MSG_PUTS(_("with X11-neXtaw GUI."));
#    else
    MSG_PUTS(_("with X11-Athena GUI."));
#    endif
#   else
#     ifdef FEAT_GUI_PHOTON
    MSG_PUTS(_("with Photon GUI."));
#     else
#      if defined(MSWIN)
    MSG_PUTS(_("with GUI."));
#      else
#	if defined(FEAT_GUI_MACVIM)
    MSG_PUTS(_("with MacVim GUI."));
#	else
#	 if defined(TARGET_API_MAC_CARBON) && TARGET_API_MAC_CARBON
    MSG_PUTS(_("with Carbon GUI."));
#	 else
#	  if defined(TARGET_API_MAC_OSX) && TARGET_API_MAC_OSX
    MSG_PUTS(_("with Cocoa GUI."));
#	  else
#	   if defined(MACOS)
    MSG_PUTS(_("with (classic) GUI."));
#	   endif
#         endif
#	 endif
#	endif
#      endif
#    endif
#   endif
#  endif
# endif
#endif
    version_msg(_("  Features included (+) or not (-):\n"));

    list_features();

#ifdef SYS_VIMRC_FILE
    version_msg(_("   system vimrc file: \""));
    version_msg(SYS_VIMRC_FILE);
    version_msg("\"\n");
#endif
#ifdef USR_VIMRC_FILE
    version_msg(_("     user vimrc file: \""));
    version_msg(USR_VIMRC_FILE);
    version_msg("\"\n");
#endif
#ifdef USR_VIMRC_FILE2
    version_msg(_(" 2nd user vimrc file: \""));
    version_msg(USR_VIMRC_FILE2);
    version_msg("\"\n");
#endif
#ifdef USR_VIMRC_FILE3
    version_msg(_(" 3rd user vimrc file: \""));
    version_msg(USR_VIMRC_FILE3);
    version_msg("\"\n");
#endif
#ifdef USR_EXRC_FILE
    version_msg(_("      user exrc file: \""));
    version_msg(USR_EXRC_FILE);
    version_msg("\"\n");
#endif
#ifdef USR_EXRC_FILE2
    version_msg(_("  2nd user exrc file: \""));
    version_msg(USR_EXRC_FILE2);
    version_msg("\"\n");
#endif
#ifdef FEAT_GUI
# ifdef SYS_GVIMRC_FILE
    version_msg(_("  system gvimrc file: \""));
    version_msg(SYS_GVIMRC_FILE);
    version_msg("\"\n");
# endif
    version_msg(_("    user gvimrc file: \""));
    version_msg(USR_GVIMRC_FILE);
    version_msg("\"\n");
# ifdef USR_GVIMRC_FILE2
    version_msg(_("2nd user gvimrc file: \""));
    version_msg(USR_GVIMRC_FILE2);
    version_msg("\"\n");
# endif
# ifdef USR_GVIMRC_FILE3
    version_msg(_("3rd user gvimrc file: \""));
    version_msg(USR_GVIMRC_FILE3);
    version_msg("\"\n");
# endif
#endif
#ifdef FEAT_GUI
# ifdef SYS_MENU_FILE
    version_msg(_("    system menu file: \""));
    version_msg(SYS_MENU_FILE);
    version_msg("\"\n");
# endif
#endif
#ifdef HAVE_PATHDEF
    if (*default_vim_dir != NUL)
    {
	version_msg(_("  fall-back for $VIM: \""));
	version_msg((char *)default_vim_dir);
	version_msg("\"\n");
    }
    if (*default_vimruntime_dir != NUL)
    {
	version_msg(_(" f-b for $VIMRUNTIME: \""));
	version_msg((char *)default_vimruntime_dir);
	version_msg("\"\n");
    }
    version_msg(_("Compilation: "));
    version_msg((char *)all_cflags);
    version_msg("\n");
#ifdef VMS
    if (*compiler_version != NUL)
    {
	version_msg(_("Compiler: "));
	version_msg((char *)compiler_version);
	version_msg("\n");
    }
#endif
    version_msg(_("Linking: "));
    version_msg((char *)all_lflags);
#endif
#ifdef DEBUG
    version_msg("\n");
    version_msg(_("  DEBUG BUILD"));
#endif
}