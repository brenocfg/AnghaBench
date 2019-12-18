#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  hMainWnd; } ;
struct TYPE_8__ {struct TYPE_8__* hGrpFile; int /*<<< orphan*/  bOverwriteFileOk; int /*<<< orphan*/  bFileNameModified; } ;
typedef  TYPE_1__ PROGGROUP ;
typedef  int /*<<< orphan*/  OFSTRUCT ;
typedef  scalar_t__ HFILE ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GRPFILE_DoWriteGroupFile (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  GRPFILE_ModifyFileName (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 TYPE_4__ Globals ; 
 scalar_t__ HFILE_ERROR ; 
 scalar_t__ IDCANCEL ; 
 scalar_t__ IDOK ; 
 int /*<<< orphan*/  IDS_ERROR ; 
 int /*<<< orphan*/  IDS_FILE_NOT_OVERWRITTEN_s ; 
 int /*<<< orphan*/  IDS_FILE_WRITE_ERROR_s ; 
 int /*<<< orphan*/  IDS_INFO ; 
 int /*<<< orphan*/  IDS_SAVE_GROUP_AS_s ; 
 TYPE_1__* LocalLock (TYPE_1__*) ; 
 scalar_t__ MAIN_MessageBoxIDS_s (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int MAX_PATHNAME_LEN ; 
 int MB_DEFBUTTON2 ; 
 int MB_ICONINFORMATION ; 
 int MB_OK ; 
 int MB_OKCANCEL ; 
 scalar_t__ MessageBoxA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  OF_EXIST ; 
 scalar_t__ OpenFile (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _lclose (scalar_t__) ; 
 scalar_t__ _lcreat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wsprintfA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

BOOL GRPFILE_WriteGroupFile(PROGGROUP* hGroup)
{
#if 0
  CHAR szPath[MAX_PATHNAME_LEN];
  PROGGROUP *group = LocalLock(hGroup);
  OFSTRUCT dummy;
  HFILE file;
  BOOL ret;

  GRPFILE_ModifyFileName(szPath, LocalLock(group->hGrpFile),
			 MAX_PATHNAME_LEN,
			 group->bFileNameModified);

  /* Try not to overwrite original files */

  /* group->bOverwriteFileOk == TRUE only if a file has the modified format */
  if (!group->bOverwriteFileOk &&
      OpenFile(szPath, &dummy, OF_EXIST) != HFILE_ERROR)
    {
      /* Original file exists, try `.gr' extension */
      GRPFILE_ModifyFileName(szPath, LocalLock(group->hGrpFile),
			     MAX_PATHNAME_LEN, TRUE);
      if (OpenFile(szPath, &dummy, OF_EXIST) != HFILE_ERROR)
	{
	  /* File exists. Do not overwrite */
	  MAIN_MessageBoxIDS_s(IDS_FILE_NOT_OVERWRITTEN_s, szPath,
			       IDS_INFO, MB_OK);
	  return FALSE;
	}
      /* Inform about the modified file name */
      if (IDCANCEL ==
	  MAIN_MessageBoxIDS_s(IDS_SAVE_GROUP_AS_s, szPath, IDS_INFO,
			       MB_OKCANCEL | MB_ICONINFORMATION))
	return FALSE;
    }

  {
    /* Warn about the (possible) incompatibility */
    CHAR msg[MAX_PATHNAME_LEN + 200];
    wsprintfA(msg,
	     "Group files written by this DRAFT Program Manager "
	     "possibly cannot be read by the Microsoft Program Manager!!\n"
	     "Are you sure to write %s?", szPath);
    if (IDOK != MessageBoxA(Globals.hMainWnd, msg, "WARNING",
                            MB_OKCANCEL | MB_DEFBUTTON2)) return FALSE;
  }

  /* Open file */
  file = _lcreat(szPath, 0);
  if (file != HFILE_ERROR)
    {
      ret = GRPFILE_DoWriteGroupFile(file, group);
      _lclose(file);
    }
  else ret = FALSE;

  if (!ret)
    MAIN_MessageBoxIDS_s(IDS_FILE_WRITE_ERROR_s, szPath, IDS_ERROR, MB_OK);

  return(ret);

#else
    return TRUE;
#endif
}