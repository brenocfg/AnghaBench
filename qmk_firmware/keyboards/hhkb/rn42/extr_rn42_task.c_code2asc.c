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
typedef  int uint8_t ;

/* Variables and functions */
#define  KC_0 181 
#define  KC_1 180 
#define  KC_2 179 
#define  KC_3 178 
#define  KC_4 177 
#define  KC_5 176 
#define  KC_6 175 
#define  KC_7 174 
#define  KC_8 173 
#define  KC_9 172 
#define  KC_A 171 
#define  KC_B 170 
#define  KC_BSLASH 169 
#define  KC_BSPACE 168 
#define  KC_C 167 
#define  KC_COMMA 166 
#define  KC_D 165 
#define  KC_DELETE 164 
#define  KC_DOT 163 
#define  KC_E 162 
#define  KC_ENTER 161 
#define  KC_EQUAL 160 
#define  KC_ESCAPE 159 
#define  KC_F 158 
#define  KC_G 157 
#define  KC_GRAVE 156 
#define  KC_H 155 
#define  KC_I 154 
#define  KC_J 153 
#define  KC_K 152 
#define  KC_L 151 
#define  KC_LBRACKET 150 
 int /*<<< orphan*/  KC_LSHIFT ; 
#define  KC_M 149 
#define  KC_MINUS 148 
#define  KC_N 147 
#define  KC_NONUS_HASH 146 
#define  KC_O 145 
#define  KC_P 144 
#define  KC_Q 143 
#define  KC_QUOTE 142 
#define  KC_R 141 
#define  KC_RBRACKET 140 
 int /*<<< orphan*/  KC_RSHIFT ; 
#define  KC_S 139 
#define  KC_SCOLON 138 
#define  KC_SLASH 137 
#define  KC_SPACE 136 
#define  KC_T 135 
#define  KC_TAB 134 
#define  KC_U 133 
#define  KC_V 132 
#define  KC_W 131 
#define  KC_X 130 
#define  KC_Y 129 
#define  KC_Z 128 
 int MOD_BIT (int /*<<< orphan*/ ) ; 
 int get_mods () ; 

__attribute__((used)) static uint8_t code2asc(uint8_t code)
{
    bool shifted = (get_mods() & (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))) ? true : false;
    switch (code) {
        case KC_A: return (shifted ? 'A' : 'a');
        case KC_B: return (shifted ? 'B' : 'b');
        case KC_C: return (shifted ? 'C' : 'c');
        case KC_D: return (shifted ? 'D' : 'd');
        case KC_E: return (shifted ? 'E' : 'e');
        case KC_F: return (shifted ? 'F' : 'f');
        case KC_G: return (shifted ? 'G' : 'g');
        case KC_H: return (shifted ? 'H' : 'h');
        case KC_I: return (shifted ? 'I' : 'i');
        case KC_J: return (shifted ? 'J' : 'j');
        case KC_K: return (shifted ? 'K' : 'k');
        case KC_L: return (shifted ? 'L' : 'l');
        case KC_M: return (shifted ? 'M' : 'm');
        case KC_N: return (shifted ? 'N' : 'n');
        case KC_O: return (shifted ? 'O' : 'o');
        case KC_P: return (shifted ? 'P' : 'p');
        case KC_Q: return (shifted ? 'Q' : 'q');
        case KC_R: return (shifted ? 'R' : 'r');
        case KC_S: return (shifted ? 'S' : 's');
        case KC_T: return (shifted ? 'T' : 't');
        case KC_U: return (shifted ? 'U' : 'u');
        case KC_V: return (shifted ? 'V' : 'v');
        case KC_W: return (shifted ? 'W' : 'w');
        case KC_X: return (shifted ? 'X' : 'x');
        case KC_Y: return (shifted ? 'Y' : 'y');
        case KC_Z: return (shifted ? 'Z' : 'z');
        case KC_1: return (shifted ? '!' : '1');
        case KC_2: return (shifted ? '@' : '2');
        case KC_3: return (shifted ? '#' : '3');
        case KC_4: return (shifted ? '$' : '4');
        case KC_5: return (shifted ? '%' : '5');
        case KC_6: return (shifted ? '^' : '6');
        case KC_7: return (shifted ? '&' : '7');
        case KC_8: return (shifted ? '*' : '8');
        case KC_9: return (shifted ? '(' : '9');
        case KC_0: return (shifted ? ')' : '0');
        case KC_ENTER: return '\n';
        case KC_ESCAPE: return 0x1B;
        case KC_BSPACE: return '\b';
        case KC_TAB: return '\t';
        case KC_SPACE: return ' ';
        case KC_MINUS: return (shifted ? '_' : '-');
        case KC_EQUAL: return (shifted ? '+' : '=');
        case KC_LBRACKET: return (shifted ? '{' : '[');
        case KC_RBRACKET: return (shifted ? '}' : ']');
        case KC_BSLASH: return (shifted ? '|' : '\\');
        case KC_NONUS_HASH: return (shifted ? '|' : '\\');
        case KC_SCOLON: return (shifted ? ':' : ';');
        case KC_QUOTE: return (shifted ? '"' : '\'');
        case KC_GRAVE: return (shifted ? '~' : '`');
        case KC_COMMA: return (shifted ? '<' : ',');
        case KC_DOT: return (shifted ? '>' : '.');
        case KC_SLASH: return (shifted ? '?' : '/');
        case KC_DELETE: return '\0';    // Delete to disconnect
        default: return ' ';
    }
}