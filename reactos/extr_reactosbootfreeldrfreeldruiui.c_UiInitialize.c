#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ VIDEODISPLAYMODE ;
typedef  int /*<<< orphan*/  ULONG_PTR ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_5__ {int /*<<< orphan*/  (* Initialize ) () ;} ;
typedef  int /*<<< orphan*/  SettingText ;
typedef  int /*<<< orphan*/  DisplayModeText ;
typedef  char CHAR ;
typedef  int BOOLEAN ;

/* Variables and functions */
 int FALSE ; 
 TYPE_1__ GuiVtbl ; 
 scalar_t__ IniOpenSection (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ IniReadSettingByName (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  MachVideoGetDisplaySize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ MachVideoSetDisplayMode (char*,int) ; 
 TYPE_1__ MiniTuiVtbl ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int TRUE ; 
 TYPE_1__ TuiVtbl ; 
 void* UiBackdropBgColor ; 
 void* UiBackdropFgColor ; 
 int /*<<< orphan*/  UiBackdropFillStyle ; 
 int UiCenterMenu ; 
 int UiDrawTime ; 
 void* UiEditBoxBgColor ; 
 void* UiEditBoxTextColor ; 
 int /*<<< orphan*/  UiFadeInBackdrop () ; 
 void* UiMenuBgColor ; 
 int UiMenuBox ; 
 void* UiMenuFgColor ; 
 void* UiMessageBoxBgColor ; 
 void* UiMessageBoxFgColor ; 
 int /*<<< orphan*/  UiScreenHeight ; 
 int /*<<< orphan*/  UiScreenWidth ; 
 void* UiSelectedTextBgColor ; 
 void* UiSelectedTextColor ; 
 void* UiStatusBarBgColor ; 
 void* UiStatusBarFgColor ; 
 void* UiTextColor ; 
 void* UiTextToColor (char*) ; 
 int /*<<< orphan*/  UiTextToFillStyle (char*) ; 
 int /*<<< orphan*/  UiTimeText ; 
 void* UiTitleBoxBgColor ; 
 void* UiTitleBoxFgColor ; 
 int /*<<< orphan*/  UiTitleBoxTitleText ; 
 int UiUseSpecialEffects ; 
 TYPE_1__ UiVtbl ; 
 scalar_t__ VideoTextMode ; 
 scalar_t__ _stricmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 

BOOLEAN UiInitialize(BOOLEAN ShowGui)
{
    VIDEODISPLAYMODE    UiDisplayMode; // Tells us if we are in text or graphics mode
    BOOLEAN UiMinimal = FALSE; // Tells us if we are using a minimal console-like UI
    ULONG_PTR SectionId;
    CHAR    DisplayModeText[260];
    CHAR    SettingText[260];
    ULONG    Depth;

    if (!ShowGui)
    {
        if (!UiVtbl.Initialize())
        {
            MachVideoSetDisplayMode(NULL, FALSE);
            return FALSE;
        }
        return TRUE;
    }

    TRACE("Initializing User Interface.\n");
    TRACE("Reading in UI settings from [Display] section.\n");

    DisplayModeText[0] = '\0';
    if (IniOpenSection("Display", &SectionId))
    {
        if (!IniReadSettingByName(SectionId, "DisplayMode", DisplayModeText, sizeof(DisplayModeText)))
        {
            DisplayModeText[0] = '\0';
        }
        if (IniReadSettingByName(SectionId, "MinimalUI", SettingText, sizeof(SettingText)))
        {
            UiMinimal = (_stricmp(SettingText, "Yes") == 0 && strlen(SettingText) == 3);
        }
    }

    UiDisplayMode = MachVideoSetDisplayMode(DisplayModeText, TRUE);
    MachVideoGetDisplaySize(&UiScreenWidth, &UiScreenHeight, &Depth);

    if (VideoTextMode == UiDisplayMode)
        UiVtbl = (UiMinimal ? MiniTuiVtbl : TuiVtbl);
    else
        UiVtbl = GuiVtbl;

    if (!UiVtbl.Initialize())
    {
        MachVideoSetDisplayMode(NULL, FALSE);
        return FALSE;
    }

    if (IniOpenSection("Display", &SectionId))
    {
        if (IniReadSettingByName(SectionId, "TitleText", SettingText, sizeof(SettingText)))
        {
            strcpy(UiTitleBoxTitleText, SettingText);
        }
        if (IniReadSettingByName(SectionId, "TimeText", SettingText, sizeof(SettingText)))
        {
            strcpy(UiTimeText, SettingText);
        }
        if (IniReadSettingByName(SectionId, "StatusBarColor", SettingText, sizeof(SettingText)))
        {
            UiStatusBarBgColor = UiTextToColor(SettingText);
        }
        if (IniReadSettingByName(SectionId, "StatusBarTextColor", SettingText, sizeof(SettingText)))
        {
            UiStatusBarFgColor = UiTextToColor(SettingText);
        }
        if (IniReadSettingByName(SectionId, "BackdropTextColor", SettingText, sizeof(SettingText)))
        {
            UiBackdropFgColor = UiTextToColor(SettingText);
        }
        if (IniReadSettingByName(SectionId, "BackdropColor", SettingText, sizeof(SettingText)))
        {
            UiBackdropBgColor = UiTextToColor(SettingText);
        }
        if (IniReadSettingByName(SectionId, "BackdropFillStyle", SettingText, sizeof(SettingText)))
        {
            UiBackdropFillStyle = UiTextToFillStyle(SettingText);
        }
        if (IniReadSettingByName(SectionId, "TitleBoxTextColor", SettingText, sizeof(SettingText)))
        {
            UiTitleBoxFgColor = UiTextToColor(SettingText);
        }
        if (IniReadSettingByName(SectionId, "TitleBoxColor", SettingText, sizeof(SettingText)))
        {
            UiTitleBoxBgColor = UiTextToColor(SettingText);
        }
        if (IniReadSettingByName(SectionId, "MessageBoxTextColor", SettingText, sizeof(SettingText)))
        {
            UiMessageBoxFgColor = UiTextToColor(SettingText);
        }
        if (IniReadSettingByName(SectionId, "MessageBoxColor", SettingText, sizeof(SettingText)))
        {
            UiMessageBoxBgColor = UiTextToColor(SettingText);
        }
        if (IniReadSettingByName(SectionId, "MenuTextColor", SettingText, sizeof(SettingText)))
        {
            UiMenuFgColor = UiTextToColor(SettingText);
        }
        if (IniReadSettingByName(SectionId, "MenuColor", SettingText, sizeof(SettingText)))
        {
            UiMenuBgColor = UiTextToColor(SettingText);
        }
        if (IniReadSettingByName(SectionId, "TextColor", SettingText, sizeof(SettingText)))
        {
            UiTextColor = UiTextToColor(SettingText);
        }
        if (IniReadSettingByName(SectionId, "SelectedTextColor", SettingText, sizeof(SettingText)))
        {
            UiSelectedTextColor = UiTextToColor(SettingText);
        }
        if (IniReadSettingByName(SectionId, "SelectedColor", SettingText, sizeof(SettingText)))
        {
            UiSelectedTextBgColor = UiTextToColor(SettingText);
        }
        if (IniReadSettingByName(SectionId, "EditBoxTextColor", SettingText, sizeof(SettingText)))
        {
            UiEditBoxTextColor = UiTextToColor(SettingText);
        }
        if (IniReadSettingByName(SectionId, "EditBoxColor", SettingText, sizeof(SettingText)))
        {
            UiEditBoxBgColor = UiTextToColor(SettingText);
        }
        if (IniReadSettingByName(SectionId, "SpecialEffects", SettingText, sizeof(SettingText)))
        {
            UiUseSpecialEffects = (_stricmp(SettingText, "Yes") == 0 && strlen(SettingText) == 3);
        }
        if (IniReadSettingByName(SectionId, "ShowTime", SettingText, sizeof(SettingText)))
        {
            UiDrawTime = (_stricmp(SettingText, "Yes") == 0 && strlen(SettingText) == 3);
        }
        if (IniReadSettingByName(SectionId, "MenuBox", SettingText, sizeof(SettingText)))
        {
            UiMenuBox = (_stricmp(SettingText, "Yes") == 0 && strlen(SettingText) == 3);
        }
        if (IniReadSettingByName(SectionId, "CenterMenu", SettingText, sizeof(SettingText)))
        {
            UiCenterMenu = (_stricmp(SettingText, "Yes") == 0 && strlen(SettingText) == 3);
        }
    }

    // Draw the backdrop and fade it in if special effects are enabled
    UiFadeInBackdrop();

    TRACE("UiInitialize() returning TRUE.\n");
    return TRUE;
}