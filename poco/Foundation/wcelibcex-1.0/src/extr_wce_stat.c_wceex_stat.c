#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct stat {int st_nlink; scalar_t__ st_uid; scalar_t__ st_ino; scalar_t__ st_gid; scalar_t__ st_dev; scalar_t__ st_rdev; scalar_t__ st_size; int /*<<< orphan*/  st_mode; void* st_mtime; void* st_ctime; void* st_atime; } ;
struct TYPE_5__ {scalar_t__ dwHighDateTime; scalar_t__ dwLowDateTime; } ;
struct TYPE_4__ {char* cFileName; scalar_t__ nFileSizeLow; int /*<<< orphan*/  dwFileAttributes; TYPE_3__ ftCreationTime; TYPE_3__ ftLastAccessTime; TYPE_3__ ftLastWriteTime; scalar_t__ nFileSizeHigh; } ;
typedef  TYPE_1__ WIN32_FIND_DATA ;
typedef  int /*<<< orphan*/  SYSTEMTIME ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  FILETIME ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_ATTRIBUTE_DIRECTORY ; 
 int /*<<< orphan*/  FileTimeToLocalFileTime (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FileTimeToSystemTime (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FindClose (scalar_t__) ; 
 scalar_t__ FindFirstFile (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 scalar_t__ TM_YEAR_BASE ; 
 int /*<<< orphan*/  __wceex_get_file_mode (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ _stricmp (char const*,char*) ; 
 int /*<<< orphan*/  mbstowcs (int /*<<< orphan*/ *,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strpbrk (char const*,char*) ; 
 void* wceex_local_to_time (int /*<<< orphan*/ *) ; 
 void* wceex_local_to_time_r (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int wceex_stat(const char* filename, struct stat *buffer)
{
    HANDLE findhandle;
    WIN32_FIND_DATA findbuf;
    wchar_t pathWCE[MAX_PATH];

    //Don't allow wildcards to be interpreted by system
    if(strpbrk(filename, "?*"))
        //if(wcspbrk(path, L"?*"))
    {
        //errno = ENOENT;
        return(-1);
    }

    //search file/dir
    mbstowcs(pathWCE, filename, strlen(filename) + 1);
    findhandle = FindFirstFile(pathWCE, &findbuf);
    if(findhandle == INVALID_HANDLE_VALUE)
    {
        //is root
        if(_stricmp(filename, ".\\")==0)
        {
            findbuf.dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;

            //dummy values
            findbuf.nFileSizeHigh = 0;
            findbuf.nFileSizeLow = 0;
            findbuf.cFileName[0] = '\0';

            buffer->st_mtime = wceex_local_to_time_r(1980 - TM_YEAR_BASE, 0, 1, 0, 0, 0);
            buffer->st_atime = buffer->st_mtime;
            buffer->st_ctime = buffer->st_mtime;
        }

        //treat as an error
        else
        {
            //errno = ENOENT;
            return(-1);
        }
    }
    else
    {
        /* File is found*/

        SYSTEMTIME SystemTime;
        FILETIME LocalFTime;

        //Time of last modification
        if(!FileTimeToLocalFileTime( &findbuf.ftLastWriteTime, &LocalFTime) ||
            !FileTimeToSystemTime(&LocalFTime, &SystemTime))
        {
            //errno = ::GetLastError();
            FindClose( findhandle );
            return( -1 );
        }

        buffer->st_mtime = wceex_local_to_time(&SystemTime);

        //Time od last access of file
        if(findbuf.ftLastAccessTime.dwLowDateTime || findbuf.ftLastAccessTime.dwHighDateTime)
        {
            if(!FileTimeToLocalFileTime(&findbuf.ftLastAccessTime, &LocalFTime) ||
                !FileTimeToSystemTime(&LocalFTime, &SystemTime))
            {
                //errno = ::GetLastError();
                FindClose( findhandle );
                return( -1 );
            }
            buffer->st_atime = wceex_local_to_time(&SystemTime);
        }
        else
        {
            buffer->st_atime = buffer->st_mtime;
        }


        //Time of creation of file
        if(findbuf.ftCreationTime.dwLowDateTime || findbuf.ftCreationTime.dwHighDateTime)
        {
            if(!FileTimeToLocalFileTime(&findbuf.ftCreationTime, &LocalFTime) ||
                !FileTimeToSystemTime(&LocalFTime, &SystemTime))
            {
                //errno = ::GetLastError();
                FindClose( findhandle );
                return( -1 );
            }
            buffer->st_ctime = wceex_local_to_time(&SystemTime);
        }
        else
        {
            buffer->st_ctime = buffer->st_mtime;
        }

        //close handle
        FindClose(findhandle);
    }

    //file mode
    buffer->st_mode = __wceex_get_file_mode(filename, findbuf.dwFileAttributes);

    //file size
    buffer->st_size = findbuf.nFileSizeLow;

    //drive letter 0
    buffer->st_rdev = buffer->st_dev = 0;

    //set the common fields
    buffer->st_gid = 0;
    buffer->st_ino = 0;
    buffer->st_uid = 0;

    //1 dla nlink
    buffer->st_nlink = 1;


    return 0;
}