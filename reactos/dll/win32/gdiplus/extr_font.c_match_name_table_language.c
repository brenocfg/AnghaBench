#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  language_id; int /*<<< orphan*/  encoding_id; int /*<<< orphan*/  platform_id; } ;
typedef  TYPE_1__ tt_name_record ;
typedef  size_t LANGID ;

/* Variables and functions */
 size_t ARRAY_SIZE (size_t*) ; 
 int GET_BE_WORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsValidCodePage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LANG_ENGLISH ; 
 size_t MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PRIMARYLANGID (size_t) ; 
 int /*<<< orphan*/  SUBLANG_DEFAULT ; 
#define  TT_APPLE_ID_DEFAULT 135 
#define  TT_APPLE_ID_ISO_10646 134 
#define  TT_APPLE_ID_UNICODE_2_0 133 
#define  TT_MS_ID_SYMBOL_CS 132 
#define  TT_MS_ID_UNICODE_CS 131 
#define  TT_PLATFORM_APPLE_UNICODE 130 
#define  TT_PLATFORM_MACINTOSH 129 
#define  TT_PLATFORM_MICROSOFT 128 
 int /*<<< orphan*/  get_mac_code_page (TYPE_1__ const*) ; 
 size_t* mac_langid_table ; 

__attribute__((used)) static int match_name_table_language( const tt_name_record *name, LANGID lang )
{
    LANGID name_lang;

    switch (GET_BE_WORD(name->platform_id))
    {
    case TT_PLATFORM_MICROSOFT:
        switch (GET_BE_WORD(name->encoding_id))
        {
        case TT_MS_ID_UNICODE_CS:
        case TT_MS_ID_SYMBOL_CS:
            name_lang = GET_BE_WORD(name->language_id);
            break;
        default:
            return 0;
        }
        break;
    case TT_PLATFORM_MACINTOSH:
        if (!IsValidCodePage( get_mac_code_page( name ))) return 0;
        name_lang = GET_BE_WORD(name->language_id);
        if (name_lang >= ARRAY_SIZE(mac_langid_table)) return 0;
        name_lang = mac_langid_table[name_lang];
        break;
    case TT_PLATFORM_APPLE_UNICODE:
        switch (GET_BE_WORD(name->encoding_id))
        {
        case TT_APPLE_ID_DEFAULT:
        case TT_APPLE_ID_ISO_10646:
        case TT_APPLE_ID_UNICODE_2_0:
            name_lang = GET_BE_WORD(name->language_id);
            if (name_lang >= ARRAY_SIZE(mac_langid_table)) return 0;
            name_lang = mac_langid_table[name_lang];
            break;
        default:
            return 0;
        }
        break;
    default:
        return 0;
    }
    if (name_lang == lang) return 3;
    if (PRIMARYLANGID( name_lang ) == PRIMARYLANGID( lang )) return 2;
    if (name_lang == MAKELANGID( LANG_ENGLISH, SUBLANG_DEFAULT )) return 1;
    return 0;
}