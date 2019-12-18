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
struct SN_env {int* B; int c; int bra; int l; char* p; size_t ket; int* I; int lb; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_v ; 
 int in_grouping (struct SN_env*,int /*<<< orphan*/ ,int,int,int) ; 
 int out_grouping (struct SN_env*,int /*<<< orphan*/ ,int,int,int) ; 
 int r_Step_1a (struct SN_env*) ; 
 int r_Step_1b (struct SN_env*) ; 
 int r_Step_1c (struct SN_env*) ; 
 int r_Step_2 (struct SN_env*) ; 
 int r_Step_3 (struct SN_env*) ; 
 int r_Step_4 (struct SN_env*) ; 
 int r_Step_5a (struct SN_env*) ; 
 int r_Step_5b (struct SN_env*) ; 
 int /*<<< orphan*/  s_21 ; 
 int /*<<< orphan*/  s_22 ; 
 int /*<<< orphan*/  s_23 ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

extern int porter_ISO_8859_1_stem(struct SN_env * z) { /* forwardmode */
    z->B[0] = 0; /* unset Y_found, line 115 */
    {   int c1 = z->c; /* do, line 116 */
        z->bra = z->c; /* [, line 116 */
        if (z->c == z->l || z->p[z->c] != 'y') goto lab0; /* literal, line 116 */
        z->c++;
        z->ket = z->c; /* ], line 116 */
        {   int ret = slice_from_s(z, 1, s_21); /* <-, line 116 */
            if (ret < 0) return ret;
        }
        z->B[0] = 1; /* set Y_found, line 116 */
    lab0:
        z->c = c1;
    }
    {   int c2 = z->c; /* do, line 117 */
        while(1) { /* repeat, line 117 */
            int c3 = z->c;
            while(1) { /* goto, line 117 */
                int c4 = z->c;
                if (in_grouping(z, g_v, 97, 121, 0)) goto lab3; /* grouping v, line 117 */
                z->bra = z->c; /* [, line 117 */
                if (z->c == z->l || z->p[z->c] != 'y') goto lab3; /* literal, line 117 */
                z->c++;
                z->ket = z->c; /* ], line 117 */
                z->c = c4;
                break;
            lab3:
                z->c = c4;
                if (z->c >= z->l) goto lab2;
                z->c++; /* goto, line 117 */
            }
            {   int ret = slice_from_s(z, 1, s_22); /* <-, line 117 */
                if (ret < 0) return ret;
            }
            z->B[0] = 1; /* set Y_found, line 117 */
            continue;
        lab2:
            z->c = c3;
            break;
        }
        z->c = c2;
    }
    z->I[0] = z->l; /* $p1 = <integer expression>, line 119 */
    z->I[1] = z->l; /* $p2 = <integer expression>, line 120 */
    {   int c5 = z->c; /* do, line 121 */
        {    /* gopast */ /* grouping v, line 122 */
            int ret = out_grouping(z, g_v, 97, 121, 1);
            if (ret < 0) goto lab4;
            z->c += ret;
        }
        {    /* gopast */ /* non v, line 122 */
            int ret = in_grouping(z, g_v, 97, 121, 1);
            if (ret < 0) goto lab4;
            z->c += ret;
        }
        z->I[0] = z->c; /* setmark p1, line 122 */
        {    /* gopast */ /* grouping v, line 123 */
            int ret = out_grouping(z, g_v, 97, 121, 1);
            if (ret < 0) goto lab4;
            z->c += ret;
        }
        {    /* gopast */ /* non v, line 123 */
            int ret = in_grouping(z, g_v, 97, 121, 1);
            if (ret < 0) goto lab4;
            z->c += ret;
        }
        z->I[1] = z->c; /* setmark p2, line 123 */
    lab4:
        z->c = c5;
    }
    z->lb = z->c; z->c = z->l; /* backwards, line 126 */

    {   int m6 = z->l - z->c; (void)m6; /* do, line 127 */
        {   int ret = r_Step_1a(z); /* call Step_1a, line 127 */
            if (ret == 0) goto lab5;
            if (ret < 0) return ret;
        }
    lab5:
        z->c = z->l - m6;
    }
    {   int m7 = z->l - z->c; (void)m7; /* do, line 128 */
        {   int ret = r_Step_1b(z); /* call Step_1b, line 128 */
            if (ret == 0) goto lab6;
            if (ret < 0) return ret;
        }
    lab6:
        z->c = z->l - m7;
    }
    {   int m8 = z->l - z->c; (void)m8; /* do, line 129 */
        {   int ret = r_Step_1c(z); /* call Step_1c, line 129 */
            if (ret == 0) goto lab7;
            if (ret < 0) return ret;
        }
    lab7:
        z->c = z->l - m8;
    }
    {   int m9 = z->l - z->c; (void)m9; /* do, line 130 */
        {   int ret = r_Step_2(z); /* call Step_2, line 130 */
            if (ret == 0) goto lab8;
            if (ret < 0) return ret;
        }
    lab8:
        z->c = z->l - m9;
    }
    {   int m10 = z->l - z->c; (void)m10; /* do, line 131 */
        {   int ret = r_Step_3(z); /* call Step_3, line 131 */
            if (ret == 0) goto lab9;
            if (ret < 0) return ret;
        }
    lab9:
        z->c = z->l - m10;
    }
    {   int m11 = z->l - z->c; (void)m11; /* do, line 132 */
        {   int ret = r_Step_4(z); /* call Step_4, line 132 */
            if (ret == 0) goto lab10;
            if (ret < 0) return ret;
        }
    lab10:
        z->c = z->l - m11;
    }
    {   int m12 = z->l - z->c; (void)m12; /* do, line 133 */
        {   int ret = r_Step_5a(z); /* call Step_5a, line 133 */
            if (ret == 0) goto lab11;
            if (ret < 0) return ret;
        }
    lab11:
        z->c = z->l - m12;
    }
    {   int m13 = z->l - z->c; (void)m13; /* do, line 134 */
        {   int ret = r_Step_5b(z); /* call Step_5b, line 134 */
            if (ret == 0) goto lab12;
            if (ret < 0) return ret;
        }
    lab12:
        z->c = z->l - m13;
    }
    z->c = z->lb;
    {   int c14 = z->c; /* do, line 137 */
        if (!(z->B[0])) goto lab13; /* Boolean test Y_found, line 137 */
        while(1) { /* repeat, line 137 */
            int c15 = z->c;
            while(1) { /* goto, line 137 */
                int c16 = z->c;
                z->bra = z->c; /* [, line 137 */
                if (z->c == z->l || z->p[z->c] != 'Y') goto lab15; /* literal, line 137 */
                z->c++;
                z->ket = z->c; /* ], line 137 */
                z->c = c16;
                break;
            lab15:
                z->c = c16;
                if (z->c >= z->l) goto lab14;
                z->c++; /* goto, line 137 */
            }
            {   int ret = slice_from_s(z, 1, s_23); /* <-, line 137 */
                if (ret < 0) return ret;
            }
            continue;
        lab14:
            z->c = c15;
            break;
        }
    lab13:
        z->c = c14;
    }
    return 1;
}