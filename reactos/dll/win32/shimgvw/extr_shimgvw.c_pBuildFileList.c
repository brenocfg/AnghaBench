#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  szSearchPath ;
typedef  int /*<<< orphan*/  szFileTypes ;
struct TYPE_9__ {int /*<<< orphan*/ * cFileName; } ;
typedef  TYPE_1__ WIN32_FIND_DATAW ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  size_t UINT ;
struct TYPE_10__ {struct TYPE_10__* Prev; struct TYPE_10__* Next; int /*<<< orphan*/ * FileName; int /*<<< orphan*/  FilenameExtension; } ;
typedef  TYPE_2__ SHIMGVW_FILENODE ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  TYPE_2__ ImageCodecInfo ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 int /*<<< orphan*/  FindClose (scalar_t__) ; 
 scalar_t__ FindFirstFileW (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ FindNextFileW (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  GdipGetImageDecoders (size_t,size_t,TYPE_2__*) ; 
 int /*<<< orphan*/  GdipGetImageDecodersSize (size_t*,size_t*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  PathCombineW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PathRemoveFileSpecW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StringCbCopyW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StringCchCopyW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 void* malloc (int) ; 
 scalar_t__ wcscmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wcstok (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static SHIMGVW_FILENODE*
pBuildFileList(LPWSTR szFirstFile)
{
    HANDLE hFindHandle;
    WCHAR *extension;
    WCHAR szSearchPath[MAX_PATH];
    WCHAR szSearchMask[MAX_PATH];
    WCHAR szFileTypes[MAX_PATH];
    WIN32_FIND_DATAW findData;
    SHIMGVW_FILENODE *currentNode = NULL;
    SHIMGVW_FILENODE *root = NULL;
    SHIMGVW_FILENODE *conductor = NULL;
    ImageCodecInfo *codecInfo;
    UINT num;
    UINT size;
    UINT j;

    StringCbCopyW(szSearchPath, sizeof(szSearchPath), szFirstFile);
    PathRemoveFileSpecW(szSearchPath);

    GdipGetImageDecodersSize(&num, &size);
    codecInfo = malloc(size);
    if (!codecInfo)
    {
        DPRINT1("malloc() failed in pLoadFileList()\n");
        return NULL;
    }

    GdipGetImageDecoders(num, size, codecInfo);

    root = malloc(sizeof(SHIMGVW_FILENODE));
    if (!root)
    {
        DPRINT1("malloc() failed in pLoadFileList()\n");
        free(codecInfo);
        return NULL;
    }

    conductor = root;

    for (j = 0; j < num; ++j)
    {
        StringCbCopyW(szFileTypes, sizeof(szFileTypes), codecInfo[j].FilenameExtension);

        extension = wcstok(szFileTypes, L";");
        while (extension != NULL)
        {
            PathCombineW(szSearchMask, szSearchPath, extension);

            hFindHandle = FindFirstFileW(szSearchMask, &findData);
            if (hFindHandle != INVALID_HANDLE_VALUE)
            {
                do
                {
                    PathCombineW(conductor->FileName, szSearchPath, findData.cFileName);

                    // compare the name of the requested file with the one currently found.
                    // if the name matches, the current node is returned by the function.
                    if (wcscmp(szFirstFile, conductor->FileName) == 0)
                    {
                        currentNode = conductor;
                    }

                    conductor->Next = malloc(sizeof(SHIMGVW_FILENODE));

                    // if malloc fails, make circular what we have and return it
                    if (!conductor->Next)
                    {
                        DPRINT1("malloc() failed in pLoadFileList()\n");

                        conductor->Next = root;
                        root->Prev = conductor;

                        FindClose(hFindHandle);
                        free(codecInfo);
                        return conductor;
                    }

                    conductor->Next->Prev = conductor;
                    conductor = conductor->Next;
                }
                while (FindNextFileW(hFindHandle, &findData) != 0);

                FindClose(hFindHandle);
            }

            extension = wcstok(NULL, L";");
        }
    }

    // we now have a node too much in the list. In case the requested file was not found,
    // we use this node to store the name of it, otherwise we free it.
    if (currentNode == NULL)
    {
        StringCchCopyW(conductor->FileName, MAX_PATH, szFirstFile);
        currentNode = conductor;
    }
    else
    {
        conductor = conductor->Prev;
        free(conductor->Next);
    }

    // link the last node with the first one to make the list circular
    conductor->Next = root;
    root->Prev = conductor;
    conductor = currentNode;

    free(codecInfo);

    return conductor;
}