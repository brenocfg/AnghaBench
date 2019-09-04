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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ERROR_DEPENDFILENOTFOUND ; 
 int ERROR_NOTENOUGHPARAMS ; 
 int ERROR_OUTOFMEMORY ; 
 int ERROR_READERROR ; 
 int ERROR_SUCCESS ; 
 int ERROR_WRITEERROR ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 

int main(int argc, char *argv[])
{
    FILE*    DependFile;
    int        DependFileSize;
    char*    DependFileData;
    char*    NewDependFileData;
    int        CurIdx;
    int        CurIdx2;
    int        RuleDependencySplit = 0;

    // Make sure they passed enough command line parameters
    if (argc < 2)
    {
        printf("Usage: deptool srcfile.d\n");
        return ERROR_NOTENOUGHPARAMS;
    }

    // Try to open the dependency file
    DependFile = fopen(argv[1], "r+t");
    if (DependFile == NULL)
    {
        printf("deptool: No such dependency file: %s\n", argv[1]);
        return ERROR_DEPENDFILENOTFOUND;
    }

    // Get the file size
    fseek(DependFile, 0, SEEK_END);
    DependFileSize = ftell(DependFile);
    rewind(DependFile);

    // Allocate memory
    DependFileData = (char *)malloc(DependFileSize);
    NewDependFileData = (char *)malloc(DependFileSize * 3);
    if (!DependFileData || !NewDependFileData)
    {
        printf("deptool: Out of memory!\n");
        if (DependFileData != NULL)
            free(DependFileData);
        if (NewDependFileData != NULL)
            free(NewDependFileData);
        fclose(DependFile);
        return ERROR_OUTOFMEMORY;
    }
    memset(DependFileData, 0, DependFileSize);
    memset(NewDependFileData, 0, DependFileSize * 3);

    // Read in file data
    fread(DependFileData, 1, DependFileSize, DependFile);
    if (ferror(DependFile))
    {
        printf("deptool: Dependency file read error.\n");
        free(DependFileData);
        free(NewDependFileData);
        fclose(DependFile);
        return ERROR_READERROR;
    }

    // Loop through the dependency file data and
    // insert the rule for the dependency file itself
    for (CurIdx=0,CurIdx2=0; DependFileData[CurIdx]; CurIdx++,CurIdx2++)
    {
        // Find the first colon ':' in the file and insert
        // the rule right before it
        if (DependFileData[CurIdx] == ':')
        {
            NewDependFileData[CurIdx2] = ' ';
            CurIdx2++;
            strcat(&NewDependFileData[CurIdx2], argv[1]);
            CurIdx2 += strlen(argv[1]);
            NewDependFileData[CurIdx2] = ' ';
            CurIdx2++;
            strcat(NewDependFileData, &DependFileData[CurIdx]);
            CurIdx2 += 2;
            RuleDependencySplit = CurIdx + 2;
            break;
        }
        else
        {
            NewDependFileData[CurIdx2] = DependFileData[CurIdx];
        }
    }

    // Now loop through all the rule dependencies and
    // turn them into rules themselves
    strcat(NewDependFileData, "\n\n");
    CurIdx = RuleDependencySplit;
    CurIdx2 = strlen(NewDependFileData);
    for (; DependFileData[CurIdx]; CurIdx++,CurIdx2++)
    {
        // If it's a line continuation char '\' then skip over it
        if (DependFileData[CurIdx] == '\\')
        {
            CurIdx2--;
            continue;
        }

        // If it's a new line char '\n' then insert a colon ':' to make it a rule
        if (DependFileData[CurIdx] == '\n')
        {
            NewDependFileData[CurIdx2] = ':';
            CurIdx2++;
        }

        NewDependFileData[CurIdx2] = DependFileData[CurIdx];
    }

    // Write out file data
    rewind(DependFile);
    fwrite(NewDependFileData, 1, strlen(NewDependFileData), DependFile);
    if (ferror(DependFile))
    {
        printf("deptool: Dependency file write error.\n");
        fclose(DependFile);
        free(DependFileData);
        free(NewDependFileData);
        return ERROR_WRITEERROR;
    }

    fclose(DependFile);
    free(DependFileData);
    free(NewDependFileData);
    return ERROR_SUCCESS;
}