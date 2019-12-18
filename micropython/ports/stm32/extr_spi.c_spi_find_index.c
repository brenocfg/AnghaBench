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
typedef  int /*<<< orphan*/  mp_obj_t ;
struct TYPE_3__ {int /*<<< orphan*/ * spi; } ;

/* Variables and functions */
 int /*<<< orphan*/  MICROPY_HW_SPI1_NAME ; 
 int /*<<< orphan*/  MICROPY_HW_SPI2_NAME ; 
 int /*<<< orphan*/  MICROPY_HW_SPI3_NAME ; 
 int /*<<< orphan*/  MICROPY_HW_SPI4_NAME ; 
 int /*<<< orphan*/  MICROPY_HW_SPI5_NAME ; 
 int /*<<< orphan*/  MICROPY_HW_SPI6_NAME ; 
 int MP_ARRAY_SIZE (TYPE_1__*) ; 
 int mp_obj_get_int (int /*<<< orphan*/ ) ; 
 scalar_t__ mp_obj_is_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_obj_new_exception_msg_varg (int /*<<< orphan*/ *,char*,...) ; 
 char* mp_obj_str_get_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_type_ValueError ; 
 int /*<<< orphan*/  nlr_raise (int /*<<< orphan*/ ) ; 
 TYPE_1__* spi_obj ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

int spi_find_index(mp_obj_t id) {
    if (mp_obj_is_str(id)) {
        // given a string id
        const char *port = mp_obj_str_get_str(id);
        if (0) {
        #ifdef MICROPY_HW_SPI1_NAME
        } else if (strcmp(port, MICROPY_HW_SPI1_NAME) == 0) {
            return 1;
        #endif
        #ifdef MICROPY_HW_SPI2_NAME
        } else if (strcmp(port, MICROPY_HW_SPI2_NAME) == 0) {
            return 2;
        #endif
        #ifdef MICROPY_HW_SPI3_NAME
        } else if (strcmp(port, MICROPY_HW_SPI3_NAME) == 0) {
            return 3;
        #endif
        #ifdef MICROPY_HW_SPI4_NAME
        } else if (strcmp(port, MICROPY_HW_SPI4_NAME) == 0) {
            return 4;
        #endif
        #ifdef MICROPY_HW_SPI5_NAME
        } else if (strcmp(port, MICROPY_HW_SPI5_NAME) == 0) {
            return 5;
        #endif
        #ifdef MICROPY_HW_SPI6_NAME
        } else if (strcmp(port, MICROPY_HW_SPI6_NAME) == 0) {
            return 6;
        #endif
        }
        nlr_raise(mp_obj_new_exception_msg_varg(&mp_type_ValueError,
            "SPI(%s) doesn't exist", port));
    } else {
        // given an integer id
        int spi_id = mp_obj_get_int(id);
        if (spi_id >= 1 && spi_id <= MP_ARRAY_SIZE(spi_obj)
            && spi_obj[spi_id - 1].spi != NULL) {
            return spi_id;
        }
        nlr_raise(mp_obj_new_exception_msg_varg(&mp_type_ValueError,
            "SPI(%d) doesn't exist", spi_id));
    }
}