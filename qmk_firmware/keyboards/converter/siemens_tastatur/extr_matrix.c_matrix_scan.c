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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  B11 ; 
 int* matrix ; 
 int /*<<< orphan*/  matrix_scan_quantum () ; 
 int porta_buffer ; 
 int portb_buffer ; 
 scalar_t__ readPin (int /*<<< orphan*/ ) ; 
 int switch_buffer ; 

uint8_t matrix_scan(void) {
    switch_buffer = ((uint32_t)(porta_buffer & 0x7FF)) | ((uint32_t)(portb_buffer & 0x3F8) << 8);

    switch (switch_buffer) {
        case 0x1134E: matrix[0] = 0x01; break;
        case 0x3774D: matrix[0] = 0x02; break;
        case 0x10BCC: matrix[0] = 0x04; break;
        case 0x16B4B: matrix[0] = 0x08; break;
        case 0x167CA: matrix[0] = 0x10; break;
        case 0x35FC9: matrix[0] = 0x20; break;
        case 0x15B48: matrix[0] = 0x40; break;
        case 0x28347: matrix[0] = 0x80; break;
        case 0x173C6: matrix[0] = 0x100; break;
        case 0x143CF: matrix[0] = 0x200; break;
        case 0x3FDC5: matrix[0] = 0x400; break;
        case 0x3FD21: matrix[0] = 0x800; break;
        case 0x3FD77: matrix[0] = 0x1000; break;
        case 0x3FD72: matrix[0] = 0x2000; break;
        //Special pin
        case 0x3E7FA: matrix[0] = 0x8000; break;
        case 0x183EE: matrix[0] = 0x10000; break;
        case 0x197F3: matrix[0] = 0x20000; break;
        case 0x1AB7E: matrix[0] = 0x40000; break;

        case 0x107C3: matrix[1] = 0x01; break;
        case 0x3FD2E: matrix[1] = 0x02; break;
        case 0x3FD28: matrix[1] = 0x04; break;
        case 0x3FD3A: matrix[1] = 0x08; break;
        case 0x3FD2D: matrix[1] = 0x10; break;
        case 0x3FD2B: matrix[1] = 0x20; break;
        case 0x3FDA5: matrix[1] = 0x40; break;
        case 0x3FDAA: matrix[1] = 0x80; break;
        case 0x3FD36: matrix[1] = 0x100; break;
        case 0x3FD30: matrix[1] = 0x200; break;
        case 0x3FDAF: matrix[1] = 0x400; break;
        case 0x3FD22: matrix[1] = 0x800; break;
        case 0x157D4: matrix[1] = 0x1000; break;
        //Does not exist in matrix
        //Special pin
        case 0x1C778: matrix[1] = 0x8000; break;
        case 0x387ED: matrix[1] = 0x10000; break;
        case 0x19B74: matrix[1] = 0x20000; break;
        case 0x3FD7D: matrix[1] = 0x40000; break;

        //Special pin
        case 0x3FDBE: matrix[2] = 0x02; break;
        case 0x3FDAC: matrix[2] = 0x04; break;
        case 0x3FDBB: matrix[2] = 0x08; break;
        case 0x3FD39: matrix[2] = 0x10; break;
        case 0x3FDB8: matrix[2] = 0x20; break;
        case 0x3FDB7: matrix[2] = 0x40; break;
        case 0x3FD35: matrix[2] = 0x80; break;
        case 0x3FDB4: matrix[2] = 0x100; break;
        case 0x3FD33: matrix[2] = 0x200; break;
        case 0x3FDA3: matrix[2] = 0x400; break;
        case 0x3FD24: matrix[2] = 0x800; break;
        case 0x0FFDB: matrix[2] = 0x1000; break;
        case 0x3FDF5: matrix[2] = 0x2000; break;
        case 0x3FDFF: matrix[2] = 0x4000; break;
        case 0x3C3E4: matrix[2] = 0x8000; break;
        case 0x38B6C: matrix[2] = 0x10000; break;
        case 0x39FF6: matrix[2] = 0x20000; break;
        case 0x3FDFC: matrix[2] = 0x40000; break;

        //Special pin
        case 0x3FDA6: matrix[3] = 0x02; break;
        case 0x3FD27: matrix[3] = 0x04; break;
        case 0x3FD3C: matrix[3] = 0x08; break;
        case 0x3FDA9: matrix[3] = 0x10; break;
        case 0x3FDBD: matrix[3] = 0x20; break;
        case 0x3FDB1: matrix[3] = 0x40; break;
        case 0x3FDB2: matrix[3] = 0x80; break;
        case 0x30353: matrix[3] = 0x100; break;
        case 0x37BD1: matrix[3] = 0x200; break;
        case 0x363D2: matrix[3] = 0x400; break;
        case 0x3FD5F: matrix[3] = 0x800; break;
        //Does not exist in matrix
        //Does not exist in matrix
        //Special pin
        case 0x1BF00: matrix[3] = 0x8000; break;
        case 0x18FEB: matrix[3] = 0x10000; break;
        case 0x3FF69: matrix[3] = 0x20000; break;
        case 0x3A37B: matrix[3] = 0x40000; break;
        default: 
                 if ((portb_buffer & 0x1000) == 0) { matrix[1] = 0x4000; break; }
                 if ((portb_buffer & 0x2000) == 0) { matrix[3] = 0x4000; break; }
                 if ((portb_buffer & 0x4000) == 0) { matrix[0] = 0x4000; break; }
                 if ((portb_buffer & 0x8000) == 0) { matrix[2] = 0x01; break; }
                 matrix[0] = 0x00;
                 matrix[1] = 0x00;
                 matrix[2] = 0x00;
                 matrix[3] = 0x00;
    }
    //Special case for Shift
    if (readPin(B11) == 0) { matrix[3] |= 0x01; }

    porta_buffer = 65535;
    portb_buffer = 65535;

    matrix_scan_quantum();
    return 1;
}