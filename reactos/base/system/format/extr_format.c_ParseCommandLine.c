#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int WCHAR ;
struct TYPE_2__ {int* SizeString; int /*<<< orphan*/  ClusterSize; } ;
typedef  void* BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ClusterSize ; 
 void* CompressDrive ; 
 int* Drive ; 
 void* FALSE ; 
 int* FileSystem ; 
 void* GotALabel ; 
 int* Label ; 
 TYPE_1__* LegalSizes ; 
 void* QuickFormat ; 
 void* TRUE ; 
 int /*<<< orphan*/  _wcsnicmp (int*,char*,int) ; 
 int /*<<< orphan*/  wcsicmp (int*,...) ; 

__attribute__((used)) static int ParseCommandLine(int argc, WCHAR *argv[])
{
    int i, j;
    BOOLEAN gotFormat = FALSE;
    BOOLEAN gotQuick = FALSE;
    BOOLEAN gotSize = FALSE;
    BOOLEAN gotLabel = FALSE;
    BOOLEAN gotCompressed = FALSE;

    for (i = 1; i < argc; i++)
    {
        switch (argv[i][0])
        {
            case L'-': case L'/':

                if (!_wcsnicmp(&argv[i][1], L"FS:", 3))
                {
                    if (gotFormat) return -1;
                    FileSystem = &argv[i][4];
                    gotFormat = TRUE;
                }
                else if (!_wcsnicmp(&argv[i][1], L"A:", 2))
                {
                    if (gotSize) return -1;
                    j = 0;
                    while (LegalSizes[j].ClusterSize &&
                           wcsicmp(LegalSizes[j].SizeString, &argv[i][3]))
                    {
                        j++;
                    }

                    if (!LegalSizes[j].ClusterSize) return i;
                    ClusterSize = LegalSizes[j].ClusterSize;
                    gotSize = TRUE;
                }
                else if (!_wcsnicmp(&argv[i][1], L"V:", 2))
                {
                    if (gotLabel) return -1;
                    Label = &argv[i][3];
                    gotLabel = TRUE;
                    GotALabel = TRUE;
                }
                else if (!wcsicmp(&argv[i][1], L"Q"))
                {
                    if (gotQuick) return -1;
                    QuickFormat = TRUE;
                    gotQuick = TRUE;
                }
                else if (!wcsicmp(&argv[i][1], L"C"))
                {
                    if (gotCompressed) return -1;
                    CompressDrive = TRUE;
                    gotCompressed = TRUE;
                }
                else
                {
                    return i;
                }
                break;

            default:
            {
                if (Drive) return i;
                if (argv[i][1] != L':') return i;

                Drive = argv[i];
                break;
            }
        }
    }
    return 0;
}