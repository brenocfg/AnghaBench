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
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int DWORD ;

/* Variables and functions */
 int FILE_CASE_PRESERVED_NAMES ; 
 int FILE_CASE_SENSITIVE_SEARCH ; 
 int FILE_DAX_VOLUME ; 
 int FILE_FILE_COMPRESSION ; 
 int FILE_NAMED_STREAMS ; 
 int FILE_PERSISTENT_ACLS ; 
 int FILE_READ_ONLY_VOLUME ; 
 int FILE_SEQUENTIAL_WRITE_ONCE ; 
 int FILE_SUPPORTS_ENCRYPTION ; 
 int FILE_SUPPORTS_EXTENDED_ATTRIBUTES ; 
 int FILE_SUPPORTS_HARD_LINKS ; 
 int FILE_SUPPORTS_OBJECT_IDS ; 
 int FILE_SUPPORTS_OPEN_BY_FILE_ID ; 
 int FILE_SUPPORTS_REPARSE_POINTS ; 
 int FILE_SUPPORTS_SPARSE_FILES ; 
 int FILE_SUPPORTS_TRANSACTIONS ; 
 int FILE_SUPPORTS_USN_JOURNAL ; 
 int FILE_UNICODE_ON_DISK ; 
 int FILE_VOLUME_IS_COMPRESSED ; 
 int FILE_VOLUME_QUOTAS ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetVolumeInformation (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int*,int*,int*,int /*<<< orphan*/ *,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  PrintErrorMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _ftprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
VolumeInfoMain(int argc, const TCHAR *argv[])
{
    DWORD Serial, MaxComponentLen, Flags;
    TCHAR VolumeName[MAX_PATH + 1], FileSystem[MAX_PATH + 1];

#define HANDLE_FLAG(Flags, Flag, Desc) \
    if (Flags & Flag)                  \
        _ftprintf(stdout, Desc)

    /* We need a volume (path) */
    if (argc < 2)
    {
        _ftprintf(stderr, _T("Usage: fsutil fsinfo volumeinfo <volume_path>\n"));
        _ftprintf(stderr, _T("\tFor example: fsutil fsinfo volumeinfo c:\\\n"));
        return 1;
    }

    /* Gather information */
    if (!GetVolumeInformation(argv[1], VolumeName,  MAX_PATH + 1, &Serial,
                              &MaxComponentLen, &Flags, FileSystem, MAX_PATH + 1))
    {
        PrintErrorMessage(GetLastError());
        return 1;
    }

    /* Display general information */
    _ftprintf(stdout, _T("Volume name: %s\n"), VolumeName);
    _ftprintf(stdout, _T("Volume serial number: 0x%x\n"), Serial);
    _ftprintf(stdout, _T("Maximum component length: %u\n"), MaxComponentLen);
    _ftprintf(stdout, _T("File system name: %s\n"), FileSystem);

    /* Display specific flags */
    HANDLE_FLAG(Flags, FILE_CASE_SENSITIVE_SEARCH, _T("Supports case-sensitive file names\n"));
    HANDLE_FLAG(Flags, FILE_CASE_PRESERVED_NAMES, _T("Supports preserved case of file names\n"));
    HANDLE_FLAG(Flags, FILE_UNICODE_ON_DISK, _T("Supports unicode file names\n"));
    HANDLE_FLAG(Flags, FILE_PERSISTENT_ACLS, _T("Preserves and applies ACLs\n"));
    HANDLE_FLAG(Flags, FILE_FILE_COMPRESSION, _T("Supports compression per file\n"));
    HANDLE_FLAG(Flags, FILE_VOLUME_QUOTAS, _T("Supports disk quotas\n"));
    HANDLE_FLAG(Flags, FILE_SUPPORTS_SPARSE_FILES, _T("Supports sparse files\n"));
    HANDLE_FLAG(Flags, FILE_SUPPORTS_REPARSE_POINTS, _T("Supports reparse points\n"));
    HANDLE_FLAG(Flags, FILE_VOLUME_IS_COMPRESSED, _T("Is a compressed volume\n"));
    HANDLE_FLAG(Flags, FILE_SUPPORTS_OBJECT_IDS, _T("Supports object identifiers\n"));
    HANDLE_FLAG(Flags, FILE_SUPPORTS_ENCRYPTION, _T("Supports the Encrypted File System (EFS)\n"));
    HANDLE_FLAG(Flags, FILE_NAMED_STREAMS, _T("Supports named streams\n"));
    HANDLE_FLAG(Flags, FILE_READ_ONLY_VOLUME, _T("Is a read-only volume\n"));
    HANDLE_FLAG(Flags, FILE_SEQUENTIAL_WRITE_ONCE, _T("Supports a single sequential write\n"));
    HANDLE_FLAG(Flags, FILE_SUPPORTS_TRANSACTIONS, _T("Supports transactions\n"));
    HANDLE_FLAG(Flags, FILE_SUPPORTS_HARD_LINKS, _T("Supports hard links\n"));
    HANDLE_FLAG(Flags, FILE_SUPPORTS_EXTENDED_ATTRIBUTES, _T("Supports extended attributes\n"));
    HANDLE_FLAG(Flags, FILE_SUPPORTS_OPEN_BY_FILE_ID, _T("Supports opening files per file identifier\n"));
    HANDLE_FLAG(Flags, FILE_SUPPORTS_USN_JOURNAL, _T("Supports Update Sequence Number (USN) journals\n"));
    HANDLE_FLAG(Flags, FILE_DAX_VOLUME, _T("Is a direct access volume\n"));

#undef HANDLE_FLAGS

    return 0;
}