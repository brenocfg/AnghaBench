#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_1__* error; int /*<<< orphan*/  mmgr; } ;
struct TYPE_11__ {scalar_t__ error_no; } ;
typedef  int HPDF_UINT ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  TYPE_2__* HPDF_Dict ;
typedef  TYPE_2__* HPDF_Catalog ;

/* Variables and functions */
 int HPDF_CENTER_WINDOW ; 
 scalar_t__ HPDF_DICT_ITEM_NOT_FOUND ; 
 scalar_t__ HPDF_Dict_Add (TYPE_2__*,char*,TYPE_2__*) ; 
 scalar_t__ HPDF_Dict_AddBoolean (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Dict_AddName (TYPE_2__*,char*,char*) ; 
 TYPE_2__* HPDF_Dict_New (int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Dict_RemoveElement (TYPE_2__*,char*) ; 
 int HPDF_FIT_WINDOW ; 
 int HPDF_HIDE_MENUBAR ; 
 int HPDF_HIDE_TOOLBAR ; 
 int HPDF_HIDE_WINDOW_UI ; 
 scalar_t__ HPDF_OK ; 
 int HPDF_PRINT_SCALING_NONE ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_TRUE ; 

HPDF_STATUS
HPDF_Catalog_SetViewerPreference  (HPDF_Catalog   catalog,
                                   HPDF_UINT      value)
{
    HPDF_STATUS ret;
    HPDF_Dict preferences;

    HPDF_PTRACE ((" HPDF_Catalog_SetViewerPreference\n"));

    if (!value) {
        ret = HPDF_Dict_RemoveElement (catalog, "ViewerPreferences");

        if (ret == HPDF_DICT_ITEM_NOT_FOUND)
            ret = HPDF_OK;

        return ret;
    }

    preferences = HPDF_Dict_New (catalog->mmgr);
    if (!preferences)
        return catalog->error->error_no;

    if ((ret = HPDF_Dict_Add (catalog, "ViewerPreferences", preferences))
            != HPDF_OK)
        return ret;

    /*  */

    if (value & HPDF_HIDE_TOOLBAR) {
        if ((ret = HPDF_Dict_AddBoolean (preferences, "HideToolbar",
                HPDF_TRUE)) != HPDF_OK)
            return ret;
    } else {
        if ((ret = HPDF_Dict_RemoveElement (preferences, "HideToolbar")) !=
                HPDF_OK)
            if (ret != HPDF_DICT_ITEM_NOT_FOUND)
                return ret;
    }

    if (value & HPDF_HIDE_MENUBAR) {
        if ((ret = HPDF_Dict_AddBoolean (preferences, "HideMenubar",
                HPDF_TRUE)) != HPDF_OK)
            return ret;
    } else {
        if ((ret = HPDF_Dict_RemoveElement (preferences, "HideMenubar")) !=
                HPDF_OK)
            if (ret != HPDF_DICT_ITEM_NOT_FOUND)
                return ret;
    }

    if (value & HPDF_HIDE_WINDOW_UI) {
        if ((ret = HPDF_Dict_AddBoolean (preferences, "HideWindowUI",
                HPDF_TRUE)) != HPDF_OK)
            return ret;
    } else {
        if ((ret = HPDF_Dict_RemoveElement (preferences, "HideWindowUI")) !=
                HPDF_OK)
            if (ret != HPDF_DICT_ITEM_NOT_FOUND)
                return ret;
    }

    if (value & HPDF_FIT_WINDOW) {
        if ((ret = HPDF_Dict_AddBoolean (preferences, "FitWindow",
                HPDF_TRUE)) != HPDF_OK)
            return ret;
    } else {
        if ((ret = HPDF_Dict_RemoveElement (preferences, "FitWindow")) !=
                HPDF_OK)
            if (ret != HPDF_DICT_ITEM_NOT_FOUND)
                return ret;
    }

    if (value & HPDF_CENTER_WINDOW) {
        if ((ret = HPDF_Dict_AddBoolean (preferences, "CenterWindow",
                HPDF_TRUE)) != HPDF_OK)
            return ret;
    } else {
        if ((ret = HPDF_Dict_RemoveElement (preferences, "CenterWindow")) !=
                HPDF_OK)
            if (ret != HPDF_DICT_ITEM_NOT_FOUND)
                return ret;
    }

    if (value & HPDF_PRINT_SCALING_NONE) {
        if ((ret = HPDF_Dict_AddName (preferences, "PrintScaling",
                "None")) != HPDF_OK)
            return ret;
    } else {
        if ((ret = HPDF_Dict_RemoveElement (preferences, "PrintScaling")) !=
                HPDF_OK)
            if (ret != HPDF_DICT_ITEM_NOT_FOUND)
                return ret;
    }

    return HPDF_OK;
}