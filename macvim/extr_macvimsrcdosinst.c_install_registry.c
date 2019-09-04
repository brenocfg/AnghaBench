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
 int OK ; 

__attribute__((used)) static int
install_registry(void)
{
#ifdef WIN3264
    LONG	lRet = ERROR_SUCCESS;
    const char	*vim_ext_ThreadingModel = "Apartment";
    const char	*vim_ext_name = "Vim Shell Extension";
    const char	*vim_ext_clsid = "{51EEE242-AD87-11d3-9C1E-0090278BBD99}";
    char	vim_exe_path[BUFSIZE];
    char	display_name[BUFSIZE];
    char	uninstall_string[BUFSIZE];

    sprintf(vim_exe_path, "%s\\gvim.exe", installdir);

    if (install_popup)
    {
	char	    bufg[BUFSIZE];
	struct stat st;

	if (stat("gvimext.dll", &st) >= 0)
	    sprintf(bufg, "%s\\gvimext.dll", installdir);
	else
	    /* gvimext.dll is in gvimext subdir */
	    sprintf(bufg, "%s\\gvimext\\gvimext.dll", installdir);

	printf("Creating \"Edit with Vim\" popup menu entry\n");

	lRet = register_inproc_server(
	    HKEY_CLASSES_ROOT, vim_ext_clsid, vim_ext_name,
						bufg, vim_ext_ThreadingModel);
	if (ERROR_SUCCESS != lRet)
	    return FAIL;
	lRet = register_shellex(
	    HKEY_CLASSES_ROOT, vim_ext_clsid, vim_ext_name, vim_exe_path);
	if (ERROR_SUCCESS != lRet)
	    return FAIL;
    }

    if (install_openwith)
    {
	printf("Creating \"Open with ...\" list entry\n");

	lRet = register_openwith(HKEY_CLASSES_ROOT, vim_exe_path);
	if (ERROR_SUCCESS != lRet)
	    return FAIL;
    }

    printf("Creating an uninstall entry\n");

    /* For the NSIS installer use the generated uninstaller. */
    if (interactive)
    {
	sprintf(display_name, "Vim " VIM_VERSION_SHORT);
	sprintf(uninstall_string, "%s\\uninstal.exe", installdir);
    }
    else
    {
	sprintf(display_name, "Vim " VIM_VERSION_SHORT " (self-installing)");
	sprintf(uninstall_string, "%s\\uninstall-gui.exe", installdir);
    }

    lRet = register_uninstall(
	HKEY_LOCAL_MACHINE,
	"Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Vim " VIM_VERSION_SHORT,
	display_name,
	uninstall_string);
    if (ERROR_SUCCESS != lRet)
	return FAIL;
#endif /* WIN3264 */

    return OK;
}