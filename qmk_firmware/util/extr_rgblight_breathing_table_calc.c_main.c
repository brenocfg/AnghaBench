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
 int M_E ; 
 int M_PI ; 
 int RGBLIGHT_EFFECT_BREATHE_CENTER ; 
 int RGBLIGHT_EFFECT_BREATHE_MAX ; 
 int exp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sin (int) ; 

int main(void) {
    int pos, step;
    int table[256];
    for (pos = 0; pos < 256; pos ++ ) {
        table[pos] = (uint8_t)(
              (exp(sin((pos/255.0)*M_PI))- RGBLIGHT_EFFECT_BREATHE_CENTER/M_E)
              * (RGBLIGHT_EFFECT_BREATHE_MAX/(M_E-1/M_E))
              );
    }
    printf("#ifndef RGBLIGHT_EFFECT_BREATHE_TABLE\n");
    printf("#define RGBLIGHT_EFFECT_BREATHE_TABLE\n\n");
    printf("const uint8_t rgblight_effect_breathe_table[] PROGMEM = {\n");
    printf("  /* #define RGBLIGHT_EFFECT_BREATHE_CENTER   %.2f */\n", RGBLIGHT_EFFECT_BREATHE_CENTER);
    printf("  /* #define RGBLIGHT_EFFECT_BREATHE_MAX      %d */\n", RGBLIGHT_EFFECT_BREATHE_MAX);

    for (int s = 0, step = (1<<s); s < 3 ; s += 1, step = (1<<s) ) {
        printf("\n #if RGBLIGHT_BREATHE_TABLE_SIZE == %d\n",
               s == 0 ? 256:(s== 1 ? 128: 64));
        for (pos = 0; pos < 256; pos += step ) {
            printf("  0x%x%s", table[pos], (pos+step)>=256?"":"," );
            if ((pos+step) % 8 == 0)
                printf("\n");
        }
        printf(" #endif /* %d bytes table */\n", s == 0 ? 256:(s== 1 ? 128: 64));
    }
    printf("};\n");
    printf("\nstatic const int table_scale = 256/sizeof(rgblight_effect_breathe_table);\n");
    printf("\n#endif /* RGBLIGHT_EFFECT_BREATHE_TABLE */\n");
    return 0;
}