#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  enum directions { ____Placeholder_directions } directions ;
typedef  int WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  fLegacyBidiClass; } ;
typedef  TYPE_1__ SCRIPT_CONTROL ;
typedef  unsigned int DWORD ;

/* Variables and functions */
#define  AL 142 
#define  AN 141 
#define  B 140 
#define  BN 139 
#define  CS 138 
#define  EN 137 
#define  ES 136 
#define  ET 135 
 int FSI ; 
#define  L 134 
 int LRE ; 
 int LRI ; 
 int LRO ; 
 int NI ; 
#define  NSM 133 
#define  ON 132 
#define  PDF 131 
 int PDI ; 
#define  R 130 
 int RLE ; 
 int RLI ; 
 int RLO ; 
#define  S 129 
#define  WS 128 
 int get_char_typeW (int /*<<< orphan*/  const) ; 

__attribute__((used)) static void classify(const WCHAR *string, WORD *chartype, DWORD count, const SCRIPT_CONTROL *c)
{
    static const enum directions dir_map[16] =
    {
        L,  /* unassigned defaults to L */
        L,
        R,
        EN,
        ES,
        ET,
        AN,
        CS,
        B,
        S,
        WS,
        ON,
        AL,
        NSM,
        BN,
        PDF  /* also LRE, LRO, RLE, RLO */
    };

    unsigned i;

    for (i = 0; i < count; ++i)
    {
        chartype[i] = dir_map[get_char_typeW(string[i]) >> 12];
        switch (chartype[i])
        {
        case ES:
            if (!c->fLegacyBidiClass) break;
            switch (string[i])
            {
            case '-':
            case '+': chartype[i] = NI; break;
            case '/': chartype[i] = CS; break;
            }
            break;
        case PDF:
            switch (string[i])
            {
            case 0x202A: chartype[i] = LRE; break;
            case 0x202B: chartype[i] = RLE; break;
            case 0x202C: chartype[i] = PDF; break;
            case 0x202D: chartype[i] = LRO; break;
            case 0x202E: chartype[i] = RLO; break;
            case 0x2066: chartype[i] = LRI; break;
            case 0x2067: chartype[i] = RLI; break;
            case 0x2068: chartype[i] = FSI; break;
            case 0x2069: chartype[i] = PDI; break;
            }
            break;
        }
    }
}