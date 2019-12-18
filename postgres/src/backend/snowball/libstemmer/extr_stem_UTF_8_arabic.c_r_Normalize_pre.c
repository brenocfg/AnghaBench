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
struct SN_env {int c; int bra; int ket; int /*<<< orphan*/  l; int /*<<< orphan*/  p; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_0 ; 
 int find_among (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_0 ; 
 int /*<<< orphan*/  s_1 ; 
 int /*<<< orphan*/  s_10 ; 
 int /*<<< orphan*/  s_11 ; 
 int /*<<< orphan*/  s_12 ; 
 int /*<<< orphan*/  s_13 ; 
 int /*<<< orphan*/  s_14 ; 
 int /*<<< orphan*/  s_15 ; 
 int /*<<< orphan*/  s_16 ; 
 int /*<<< orphan*/  s_17 ; 
 int /*<<< orphan*/  s_18 ; 
 int /*<<< orphan*/  s_19 ; 
 int /*<<< orphan*/  s_2 ; 
 int /*<<< orphan*/  s_20 ; 
 int /*<<< orphan*/  s_21 ; 
 int /*<<< orphan*/  s_22 ; 
 int /*<<< orphan*/  s_23 ; 
 int /*<<< orphan*/  s_24 ; 
 int /*<<< orphan*/  s_25 ; 
 int /*<<< orphan*/  s_26 ; 
 int /*<<< orphan*/  s_27 ; 
 int /*<<< orphan*/  s_28 ; 
 int /*<<< orphan*/  s_29 ; 
 int /*<<< orphan*/  s_3 ; 
 int /*<<< orphan*/  s_30 ; 
 int /*<<< orphan*/  s_31 ; 
 int /*<<< orphan*/  s_32 ; 
 int /*<<< orphan*/  s_33 ; 
 int /*<<< orphan*/  s_34 ; 
 int /*<<< orphan*/  s_35 ; 
 int /*<<< orphan*/  s_36 ; 
 int /*<<< orphan*/  s_37 ; 
 int /*<<< orphan*/  s_38 ; 
 int /*<<< orphan*/  s_39 ; 
 int /*<<< orphan*/  s_4 ; 
 int /*<<< orphan*/  s_40 ; 
 int /*<<< orphan*/  s_41 ; 
 int /*<<< orphan*/  s_42 ; 
 int /*<<< orphan*/  s_43 ; 
 int /*<<< orphan*/  s_44 ; 
 int /*<<< orphan*/  s_45 ; 
 int /*<<< orphan*/  s_46 ; 
 int /*<<< orphan*/  s_47 ; 
 int /*<<< orphan*/  s_48 ; 
 int /*<<< orphan*/  s_49 ; 
 int /*<<< orphan*/  s_5 ; 
 int /*<<< orphan*/  s_6 ; 
 int /*<<< orphan*/  s_7 ; 
 int /*<<< orphan*/  s_8 ; 
 int /*<<< orphan*/  s_9 ; 
 int skip_utf8 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int slice_del (struct SN_env*) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_Normalize_pre(struct SN_env * z) { /* forwardmode */
    int among_var;
    {   int c1 = z->c; /* do, line 247 */
        while(1) { /* repeat, line 247 */
            int c2 = z->c;
            {   int c3 = z->c; /* or, line 311 */
                z->bra = z->c; /* [, line 249 */
                among_var = find_among(z, a_0, 144); /* substring, line 249 */
                if (!(among_var)) goto lab3;
                z->ket = z->c; /* ], line 249 */
                switch (among_var) { /* among, line 249 */
                    case 1:
                        {   int ret = slice_del(z); /* delete, line 250 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 2:
                        {   int ret = slice_from_s(z, 1, s_0); /* <-, line 254 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 3:
                        {   int ret = slice_from_s(z, 1, s_1); /* <-, line 255 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 4:
                        {   int ret = slice_from_s(z, 1, s_2); /* <-, line 256 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 5:
                        {   int ret = slice_from_s(z, 1, s_3); /* <-, line 257 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 6:
                        {   int ret = slice_from_s(z, 1, s_4); /* <-, line 258 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 7:
                        {   int ret = slice_from_s(z, 1, s_5); /* <-, line 259 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 8:
                        {   int ret = slice_from_s(z, 1, s_6); /* <-, line 260 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 9:
                        {   int ret = slice_from_s(z, 1, s_7); /* <-, line 261 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 10:
                        {   int ret = slice_from_s(z, 1, s_8); /* <-, line 262 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 11:
                        {   int ret = slice_from_s(z, 1, s_9); /* <-, line 263 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 12:
                        {   int ret = slice_from_s(z, 2, s_10); /* <-, line 266 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 13:
                        {   int ret = slice_from_s(z, 2, s_11); /* <-, line 267 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 14:
                        {   int ret = slice_from_s(z, 2, s_12); /* <-, line 268 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 15:
                        {   int ret = slice_from_s(z, 2, s_13); /* <-, line 269 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 16:
                        {   int ret = slice_from_s(z, 2, s_14); /* <-, line 270 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 17:
                        {   int ret = slice_from_s(z, 2, s_15); /* <-, line 271 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 18:
                        {   int ret = slice_from_s(z, 2, s_16); /* <-, line 272 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 19:
                        {   int ret = slice_from_s(z, 2, s_17); /* <-, line 273 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 20:
                        {   int ret = slice_from_s(z, 2, s_18); /* <-, line 274 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 21:
                        {   int ret = slice_from_s(z, 2, s_19); /* <-, line 275 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 22:
                        {   int ret = slice_from_s(z, 2, s_20); /* <-, line 276 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 23:
                        {   int ret = slice_from_s(z, 2, s_21); /* <-, line 277 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 24:
                        {   int ret = slice_from_s(z, 2, s_22); /* <-, line 278 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 25:
                        {   int ret = slice_from_s(z, 2, s_23); /* <-, line 279 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 26:
                        {   int ret = slice_from_s(z, 2, s_24); /* <-, line 280 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 27:
                        {   int ret = slice_from_s(z, 2, s_25); /* <-, line 281 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 28:
                        {   int ret = slice_from_s(z, 2, s_26); /* <-, line 282 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 29:
                        {   int ret = slice_from_s(z, 2, s_27); /* <-, line 283 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 30:
                        {   int ret = slice_from_s(z, 2, s_28); /* <-, line 284 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 31:
                        {   int ret = slice_from_s(z, 2, s_29); /* <-, line 285 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 32:
                        {   int ret = slice_from_s(z, 2, s_30); /* <-, line 286 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 33:
                        {   int ret = slice_from_s(z, 2, s_31); /* <-, line 287 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 34:
                        {   int ret = slice_from_s(z, 2, s_32); /* <-, line 288 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 35:
                        {   int ret = slice_from_s(z, 2, s_33); /* <-, line 289 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 36:
                        {   int ret = slice_from_s(z, 2, s_34); /* <-, line 290 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 37:
                        {   int ret = slice_from_s(z, 2, s_35); /* <-, line 291 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 38:
                        {   int ret = slice_from_s(z, 2, s_36); /* <-, line 292 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 39:
                        {   int ret = slice_from_s(z, 2, s_37); /* <-, line 293 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 40:
                        {   int ret = slice_from_s(z, 2, s_38); /* <-, line 294 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 41:
                        {   int ret = slice_from_s(z, 2, s_39); /* <-, line 295 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 42:
                        {   int ret = slice_from_s(z, 2, s_40); /* <-, line 296 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 43:
                        {   int ret = slice_from_s(z, 2, s_41); /* <-, line 297 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 44:
                        {   int ret = slice_from_s(z, 2, s_42); /* <-, line 298 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 45:
                        {   int ret = slice_from_s(z, 2, s_43); /* <-, line 299 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 46:
                        {   int ret = slice_from_s(z, 2, s_44); /* <-, line 300 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 47:
                        {   int ret = slice_from_s(z, 2, s_45); /* <-, line 301 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 48:
                        {   int ret = slice_from_s(z, 4, s_46); /* <-, line 304 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 49:
                        {   int ret = slice_from_s(z, 4, s_47); /* <-, line 305 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 50:
                        {   int ret = slice_from_s(z, 4, s_48); /* <-, line 306 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 51:
                        {   int ret = slice_from_s(z, 4, s_49); /* <-, line 307 */
                            if (ret < 0) return ret;
                        }
                        break;
                }
                goto lab2;
            lab3:
                z->c = c3;
                {   int ret = skip_utf8(z->p, z->c, 0, z->l, 1);
                    if (ret < 0) goto lab1;
                    z->c = ret; /* next, line 312 */
                }
            }
        lab2:
            continue;
        lab1:
            z->c = c2;
            break;
        }
        z->c = c1;
    }
    return 1;
}