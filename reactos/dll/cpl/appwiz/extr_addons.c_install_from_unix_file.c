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
typedef  enum install_res { ____Placeholder_install_res } install_res ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int UINT ;
typedef  char* LPWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int INSTALL_FAILED ; 
 int INSTALL_NEXT ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  _close (int) ; 
 int _open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_a (char*) ; 
 char* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 int install_file (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static enum install_res install_from_unix_file(const char *dir, const char *subdir, const char *file_name)
{
    LPWSTR dos_file_name;
    char *file_path;
    int fd, len;
    enum install_res ret;
    UINT res;

    len = strlen(dir);
    file_path = heap_alloc(len+strlen(subdir)+strlen(file_name)+3);
    if(!file_path)
        return INSTALL_FAILED;

    memcpy(file_path, dir, len);
    if(len && file_path[len-1] != '/' && file_path[len-1] != '\\')
        file_path[len++] = '/';
    if(*subdir) {
        strcpy(file_path+len, subdir);
        len += strlen(subdir);
        file_path[len++] = '/';
    }
    strcpy(file_path+len, file_name);

    fd = _open(file_path, O_RDONLY);
    if(fd == -1) {
        TRACE("%s not found\n", debugstr_a(file_path));
        heap_free(file_path);
        return INSTALL_NEXT;
    }

    _close(fd);

    WARN("Could not get wine_get_dos_file_name function, calling install_cab directly.\n");
    res = MultiByteToWideChar( CP_ACP, 0, file_path, -1, 0, 0);
    dos_file_name = heap_alloc (res*sizeof(WCHAR));
    MultiByteToWideChar( CP_ACP, 0, file_path, -1, dos_file_name, res);

    heap_free(file_path);

    ret = install_file(dos_file_name);

    heap_free(dos_file_name);
    return ret;
}