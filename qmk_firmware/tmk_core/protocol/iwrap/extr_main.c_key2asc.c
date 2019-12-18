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
#define  KC_0 180 
#define  KC_1 179 
#define  KC_2 178 
#define  KC_3 177 
#define  KC_4 176 
#define  KC_5 175 
#define  KC_6 174 
#define  KC_7 173 
#define  KC_8 172 
#define  KC_9 171 
#define  KC_A 170 
#define  KC_B 169 
#define  KC_BSLASH 168 
#define  KC_BSPACE 167 
#define  KC_C 166 
#define  KC_COMMA 165 
#define  KC_D 164 
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

__attribute__((used)) static uint8_t key2asc(uint8_t key) {
    switch (key) {
        case KC_A:
            return 'a';
        case KC_B:
            return 'b';
        case KC_C:
            return 'c';
        case KC_D:
            return 'd';
        case KC_E:
            return 'e';
        case KC_F:
            return 'f';
        case KC_G:
            return 'g';
        case KC_H:
            return 'h';
        case KC_I:
            return 'i';
        case KC_J:
            return 'j';
        case KC_K:
            return 'k';
        case KC_L:
            return 'l';
        case KC_M:
            return 'm';
        case KC_N:
            return 'n';
        case KC_O:
            return 'o';
        case KC_P:
            return 'p';
        case KC_Q:
            return 'q';
        case KC_R:
            return 'r';
        case KC_S:
            return 's';
        case KC_T:
            return 't';
        case KC_U:
            return 'u';
        case KC_V:
            return 'v';
        case KC_W:
            return 'w';
        case KC_X:
            return 'x';
        case KC_Y:
            return 'y';
        case KC_Z:
            return 'z';
        case KC_1:
            return '1';
        case KC_2:
            return '2';
        case KC_3:
            return '3';
        case KC_4:
            return '4';
        case KC_5:
            return '5';
        case KC_6:
            return '6';
        case KC_7:
            return '7';
        case KC_8:
            return '8';
        case KC_9:
            return '9';
        case KC_0:
            return '0';
        case KC_ENTER:
            return '\n';
        case KC_ESCAPE:
            return 0x1B;
        case KC_BSPACE:
            return '\b';
        case KC_TAB:
            return '\t';
        case KC_SPACE:
            return ' ';
        case KC_MINUS:
            return '-';
        case KC_EQUAL:
            return '=';
        case KC_LBRACKET:
            return '[';
        case KC_RBRACKET:
            return ']';
        case KC_BSLASH:
            return '\\';
        case KC_NONUS_HASH:
            return '\\';
        case KC_SCOLON:
            return ';';
        case KC_QUOTE:
            return '\'';
        case KC_GRAVE:
            return '`';
        case KC_COMMA:
            return ',';
        case KC_DOT:
            return '.';
        case KC_SLASH:
            return '/';
        default:
            return 0x00;
    }
}