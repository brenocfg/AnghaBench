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
typedef  char WCHAR ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  IUri ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ DWORD ;
typedef  char* BSTR ;

/* Variables and functions */
 int ARRAY_SIZE (char*) ; 
#define  DRIVE_CDROM 134 
#define  DRIVE_FIXED 133 
#define  DRIVE_NO_ROOT_DIR 132 
#define  DRIVE_RAMDISK 131 
#define  DRIVE_REMOTE 130 
#define  DRIVE_REMOVABLE 129 
#define  DRIVE_UNKNOWN 128 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int GetDriveTypeW (char*) ; 
 scalar_t__ IUri_GetPath (int /*<<< orphan*/ *,char**) ; 
 scalar_t__ IUri_GetSchemeName (int /*<<< orphan*/ *,char**) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (char*) ; 
 scalar_t__ URLZONE_INTERNET ; 
 scalar_t__ URLZONE_INVALID ; 
 scalar_t__ URLZONE_LOCAL_MACHINE ; 
 int /*<<< orphan*/  fileW ; 
 scalar_t__ get_zone_from_domains (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ get_zone_from_reg (char*,scalar_t__*) ; 
 scalar_t__ is_drive_path (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char* strchrW (char*,char) ; 
 int /*<<< orphan*/  strcmpiW (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT map_security_uri_to_zone(IUri *uri, DWORD *zone)
{
    HRESULT hres;
    BSTR scheme;

    *zone = URLZONE_INVALID;

    hres = IUri_GetSchemeName(uri, &scheme);
    if(FAILED(hres))
        return hres;

    if(!strcmpiW(scheme, fileW)) {
        BSTR path;
        WCHAR *ptr, *path_start, root[20];

        hres = IUri_GetPath(uri, &path);
        if(FAILED(hres)) {
            SysFreeString(scheme);
            return hres;
        }

        if(*path == '/' && is_drive_path(path+1))
            path_start = path+1;
        else
            path_start = path;

        if((ptr = strchrW(path_start, ':')) && ptr-path_start+1 < ARRAY_SIZE(root)) {
            UINT type;

            memcpy(root, path_start, (ptr-path_start+1)*sizeof(WCHAR));
            root[ptr-path_start+1] = 0;

            type = GetDriveTypeW(root);

            switch(type) {
            case DRIVE_UNKNOWN:
            case DRIVE_NO_ROOT_DIR:
                break;
            case DRIVE_REMOVABLE:
            case DRIVE_FIXED:
            case DRIVE_CDROM:
            case DRIVE_RAMDISK:
                *zone = URLZONE_LOCAL_MACHINE;
                hres = S_OK;
                break;
            case DRIVE_REMOTE:
                *zone = URLZONE_INTERNET;
                hres = S_OK;
                break;
            default:
                FIXME("unsupported drive type %d\n", type);
            }
        }
        SysFreeString(path);
    }

    if(*zone == URLZONE_INVALID) {
        hres = get_zone_from_domains(uri, zone);
        if(hres == S_FALSE)
            hres = get_zone_from_reg(scheme, zone);
    }

    SysFreeString(scheme);
    return hres;
}